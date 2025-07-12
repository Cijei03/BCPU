#ifdef _WIN64
	#include "lib_core.hpp"
	#include <windows.h>
	#include <fstream>
	#include <regex>
	#include <sstream>
	#include <iostream>
	#include <print>

std::string GetCPUName()
{
	DWORD DataSize = 50;
	char CPUName[50]{};
	RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString", RRF_RT_REG_SZ, nullptr, CPUName, &DataSize);
	return std::string(const_cast<const char*>(CPUName));
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