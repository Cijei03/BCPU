#include <print>
#include <iostream>
#include <regex>
#include <fstream>
#include "../lib_core.hpp"

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

int main(int argc, char* argv[])
{
	if (!DoChoice("Hello in BCPU benchmark! It will bench your CPU. Do you want proceed?"))
	{
		return 0;
	}
	
	std::println("Detected hardware concurrency: {0}", GetConcurrency());
	std::println("Benching...");
	
	PerformBenching();

	std::println("CPU Score: {0}bp", Points);
	std::println("CPU Name: {0}", GetCPUName());
	std::println("CPU Concurrency: {0}", GetConcurrency());
	std::println("Operating system: {0}", GetOSRelease());

	if (argc > 1)
	{
		if (std::string(argv[1]) == std::string("-r"))
		{
			std::ofstream File("report.txt", std::ios::trunc);
			File << "CPU Score: " << Points << "bp\n";
			File << "CPU Name: " << GetCPUName() << "\n";
			File << "CPU concurrency: " << GetConcurrency() << "\n";
			File << "Operating system: " << GetOSRelease();
		}
	}

	return 0;
}