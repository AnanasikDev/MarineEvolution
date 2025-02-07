#pragma once

#include <chrono>

extern std::uint64_t startupTime;
extern float elapsedTimeAbsolute;
extern float elapsedTimeScaled;

void computeTime();

std::uint64_t getTimeSinceUNIX();

void resetTime();