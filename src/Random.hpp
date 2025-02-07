#pragma once

#include <random>
#include <chrono>
#include "Vector.hpp"

class Random{
public:
    static void init();
    static float getFloat();
    static float getFloat(float min, float max);
    static int getInt(int min, int max);
    static Vectorf getVector(float min = -1.0f, float max = 1.0f);
    static Vectorf getVector(const Vectorf& min, const Vectorf& max);
    static int getSign();
};