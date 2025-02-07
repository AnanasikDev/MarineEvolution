#pragma once

#include <chrono>

extern std::uint64_t startupTime;
extern std::uint64_t genStartupTime;
extern float elapsedTimeAbsolute;
extern float genElapsedTimeScaled;

void computeTime();

std::uint64_t getTimeSinceUNIX();

void initTime();
void resetGenTime();