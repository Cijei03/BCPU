#ifdef __APPLE__
	#include "lib_core.hpp"
	#include <regex>
	#include <fstream>

	#define TMP_DIR "/tmp"

std::string GetCPUName()
{
	std::system("sysctl -n machdep.cpu.brand_string >> /tmp/cpu_info.txt");
	std::ifstream File("/tmp/cpu_info.txt");
	std::string Line;
	std::getline(File, Line, '\0');
	std::system("rm /tmp/cpu_info.txt");

	return Line;
}
std::string GetOSRelease()
{
	std::system("sw_vers >> /tmp/os_info.txt");
	std::ifstream File("/tmp/os_info.txt");
	std::string Line;

	std::regex Regex("([^:]+): \\W+([a-zA-Z0-9]+)");
	std::smatch Matches;
	std::stringstream Cache;

	while (std::getline(File, Line, '\n'))
	{
		std::regex_match(Line, Matches, Regex);

		if (Matches[1].str().contains("ProductName"))
		{
			Cache << Matches[2].str() << " ";
		}
		if (Matches[1].str().contains("ProductVersion"))
		{
			Cache << Matches[2].str();
		}
	}
	std::system("rm /tmp/os_info.txt");

	return Cache.rdbuf()->str();
}
#endif