#pragma once
#include <string>
#include <cstdint>
#include <atomic>

std::string GetCPUName();
std::string GetOSRelease();

void PerformBenching();
uint64_t GetConcurrency();

extern uint64_t Points;
extern std::atomic<bool> BenchInProgress;