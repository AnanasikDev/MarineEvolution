#include "Time.h"
#include "config.hpp"

std::uint64_t startupTime = 0;
float elapsedTimeAbsolute = 0;
float elapsedTimeScaled = 0;

void computeTime(){
    elapsedTimeAbsolute = (getTimeSinceUNIX() - startupTime) / 1000.0f;
    elapsedTimeScaled = elapsedTimeAbsolute * simSpeed;
}

std::uint64_t getTimeSinceUNIX() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void resetTime(){
    startupTime = getTimeSinceUNIX();
}