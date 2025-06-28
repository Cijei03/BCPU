#include <print>
#include <iostream>
#include <chrono>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>
#include <cstdint>
#include "info.hpp"
#include <regex>
#include <fstream>

std::atomic<bool> BenchInProgress = true;

bool DoChoice(const std::string& Message)
{
	std::regex Positive("y|Y");
	std::regex Negative("n|N");
	std::smatch PositiveMatch;
	std::smatch NegativeMatch;
	std::string Input;

	do
	{
		std::println("{0} (y/n)", Message);
		std::cin >> Input;

		std::regex_match(Input, PositiveMatch, Positive);
		std::regex_match(Input, NegativeMatch, Negative);
	}
	while (NegativeMatch.empty() && PositiveMatch.empty());	
	
	return !PositiveMatch.empty();
}

std::atomic<uint64_t> GlobalOperationsCount = 0;
std::atomic<uint32_t> ThreadsFinished = 0;

void Work()
{
	uint64_t OperationsCount = 0;
	glm::mat4 Cache;

	while (BenchInProgress.load())
	{
		for (uint64_t i = 0; i < UINT32_MAX; i++)
		{
			Cache = glm::rotate(Cache, 35.0f, glm::vec3(1.0f, 0.5f, 0.3f));
		}
		OperationsCount++;
	}

	GlobalOperationsCount.fetch_add(OperationsCount, std::memory_order_relaxed);
	ThreadsFinished.fetch_add(1);
}

int main(int argc, char* argv[])
{
	if (!DoChoice("Hello in BCPU benchmark! It will bench your CPU. Do you want proceed?"))
	{
		return 0;
	}

	const auto HardwareCount = std::thread::hardware_concurrency();
	std::vector<std::thread> Threads(HardwareCount);
	for (auto& T : Threads)
	{
		T = std::thread(Work);
	}
	std::println("Detected hardware concurrency: {0}", HardwareCount);
	std::println("Benching...");
	
	const auto BenchStartPoint = std::chrono::system_clock::now();

	for (auto& T : Threads)
	{
		T.detach();
	}

	while (BenchInProgress.load())
	{
		const auto BenchEndPoint = std::chrono::system_clock::now();

		BenchInProgress.store(std::chrono::duration_cast<std::chrono::seconds>(BenchEndPoint - BenchStartPoint).count() < 60);
	}

	while (ThreadsFinished.load() < HardwareCount);

	std::println("CPU Score: {0}bp", static_cast<uint64_t>(static_cast<double>(GlobalOperationsCount.load(std::memory_order_relaxed)) * 0.00000001));
	std::println("CPU Name: {0}", GetCPUName());
	std::println("CPU Concurrency: {0}", HardwareCount);
	std::println("Operating system: {0}", GetOSRelease());

	if (argc > 1)
	{
		if (std::string(argv[1]) == std::string("-r"))
		{
			std::ofstream File("report.txt", std::ios::trunc);
			File << "CPU Score: " << static_cast<uint64_t>(static_cast<double>(GlobalOperationsCount.load(std::memory_order_relaxed)) * 0.00000001) << "bp\n";
			File << "CPU Name: " << GetCPUName() << "\n";
			File << "CPU concurrency: " << HardwareCount << "\n";
			File << "Operating system: " << GetOSRelease();
		}
	}

	return 0;
}