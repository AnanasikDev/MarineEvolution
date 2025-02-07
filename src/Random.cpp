#include "Random.hpp"

void Random::init(){
    srand(time(NULL));
}

float Random::getFloat() {
		return ((float)rand() / RAND_MAX);
}

float Random::getFloat(float min, float max) {
    return getFloat() * (max - min) + min;
}

int Random::getInt(int min, int max) {
    return (int)std::round(getFloat() * (max - min) + min);
}

Vectorf Random::getVector(float min, float max){
    return Vectorf(getFloat(min, max), getFloat(min, max));
}

Vectorf Random::getVector(const Vectorf& min, const Vectorf& max){
    return Vectorf(getFloat(min.x, min.y), getFloat(max.x, max.y));
}

int Random::getSign(){
    return getFloat(-1.0f, 1.0f) >= 0 ? 1 : -1;
}