#ifdef __linux__
	#include "info.hpp"
	#include <regex>
	#include <fstream>

std::string GetCPUName()
{
	std::ifstream File("/proc/cpuinfo");
	std::string Line;

	std::regex Regex("([^:]+): (.+)");
	std::smatch Matches;

	while (std::getline(File, Line, '\n'))
	{
		std::regex_match(Line, Matches, Regex);

		if (Matches[1].str().contains("model name"))
		{
			return Matches[2].str();
		}
	}

	return "";
}
std::string GetOSRelease()
{
	std::ifstream File("/etc/os-release");
	std::string Line;

	std::regex Regex("(.+)=\"(.+)\"");
	std::smatch Matches;

	while (std::getline(File, Line, '\n'))
	{
		std::regex_match(Line, Matches, Regex);

		if (Matches[1].str().contains("PRETTY_NAME"))
		{
			return Matches[2].str();
		}
	}

	return "";
}
#endif