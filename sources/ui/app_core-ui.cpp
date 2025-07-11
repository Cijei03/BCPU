#include <print>
#include "../lib_core.hpp"
#include <SDL3/SDL.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	auto VideoMode = SDL_GetDesktopDisplayMode(*SDL_GetDisplays(nullptr));
	

	std::println("{0} {1}", VideoMode->w, VideoMode->h);

/*
	//SDL_Window* Wnd = 
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
			*/

	return 0;
}