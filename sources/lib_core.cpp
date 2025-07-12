#include "lib_core.hpp"
#include <chrono>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>
#include <cstdint>

std::atomic<bool> BenchInProgress = true;

std::atomic<uint64_t> GlobalOperationsCount = 0;
std::atomic<uint32_t> ThreadsFinished = 0;

uint64_t Points = 0;

void Work()
{
	uint64_t OperationsCount = 0;
	glm::mat4 Cache(1.0f);

	while (BenchInProgress.load())
	{
		for (uint64_t i = 0; i < UINT8_MAX && BenchInProgress.load(); i++)
		{
			Cache = glm::rotate(Cache, 35.0f, glm::vec3(1.0f, 0.5f, 0.3f));
		}
		OperationsCount++;
	}

	GlobalOperationsCount.fetch_add(OperationsCount, std::memory_order_relaxed);
	ThreadsFinished.fetch_add(1);
}

void PerformBenching()
{
	const auto HardwareCount = std::thread::hardware_concurrency();
	std::vector<std::thread> Threads(HardwareCount);
	for (auto& T : Threads)
	{
		T = std::thread(Work);
	}

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

	Points = static_cast<uint64_t>(static_cast<double>(GlobalOperationsCount.load(std::memory_order_relaxed)) * 0.000001);
}
uint64_t GetConcurrency()
{
	return std::thread::hardware_concurrency();
}