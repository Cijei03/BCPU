#ifdef _WIN64
	#include "info.hpp"
	//#include <Windows.h>
	#include <intrin.h>
	#include <fstream>
	#include <regex>
	#include <sstream>
	#include <iostream>

std::string GetCPUName()
{
	int PackedCPUInfo[4] = { -1 };
	unsigned nExIds, i = 0;
	__cpuid(PackedCPUInfo, 0x80000000);
	nExIds = PackedCPUInfo[0];
    char CPUBrandString[0x40]{};
    for (i = 0x80000000; i <= nExIds; ++i)
    {
    	__cpuid(PackedCPUInfo, i);
		
        if (i == 0x80000002)
        	memcpy(CPUBrandString, PackedCPUInfo, sizeof(PackedCPUInfo));
    	else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, PackedCPUInfo, sizeof(PackedCPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, PackedCPUInfo, sizeof(PackedCPUInfo));
    }

	return std::string(CPUBrandString);
}
std::string GetOSRelease()
{
	std::stringstream Cache;
	std::system("ver >> %tmp%\\ms_ver.txt");
    {
		std::ifstream File(std::string(std::getenv("tmp")) + "\\ms_ver.txt");
		std::string Line;
		std::getline(File, Line, '\n');
		std::getline(File, Line, '\n');
		std::regex R("([a-zA-Z]+ [a-zA-Z]+) \\[(.+)\\s([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)\\]");
		std::smatch M;

		std::regex_match(Line, M, R);

		Cache << M[1].str() << " " << M[3].str() << "." << M[4].str() << "." << M[5].str();
	}
	std::system("del %tmp%\\ms_ver.txt");
	return Cache.rdbuf()->str();
}

#endif