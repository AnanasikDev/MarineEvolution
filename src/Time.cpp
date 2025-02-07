#include "Time.h"
#include "config.hpp"

std::uint64_t startupTime = 0;
std::uint64_t genStartupTime = 0;
float elapsedTimeAbsolute = 0;
float genElapsedTimeScaled = 0;

void initTime(){
    startupTime = getTimeSinceUNIX();
    genStartupTime = startupTime;
}

void computeTime(){
    elapsedTimeAbsolute = (getTimeSinceUNIX() - startupTime) / 1000.0f;
    genElapsedTimeScaled = (getTimeSinceUNIX() - genStartupTime) / 1000.0f * simSpeed;
}

std::uint64_t getTimeSinceUNIX() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void resetGenTime(){
    genStartupTime = getTimeSinceUNIX();
}