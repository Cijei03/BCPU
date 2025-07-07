#ifdef __ANDROID__
	#include "info.hpp"
	#include <regex>
	#include <fstream>
	#include <sstream>
	#include <android/api-level.h>

std::string GetCPUName()
{
	std::ifstream File("/proc/cpuinfo");
	std::string Line;

	std::regex Regex("([^:]+): (.+)");
	std::smatch Matches;

	while (std::getline(File, Line, '\n'))
	{
		std::regex_match(Line, Matches, Regex);

		if (Matches[1].str().contains("Hardware"))
		{
			return Matches[2].str();
		}
	}

	return "";
}
std::string GetOSRelease()
{
	const auto AndroidAPILevel = android_get_device_api_level();
	if (AndroidAPILevel == -1)
	{
		return "unknown";
	}

	std::stringstream Name;
	Name << "Android L" << AndroidAPILevel;

	return Name.rdbuf()->str();
}
#endif