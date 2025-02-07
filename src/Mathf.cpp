#include "Mathf.hpp"
#include "Random.hpp"

Vectorf tanToVector(float tangent) {
    return Vectorf(1, tangent).normalized();
}

int sign(float val) {
    return val >= 0 ? 1 : -1;
}

float signf(float val) {
    return (float)sign(val);
}

float clamp(float value, float min, float max) {
    return value > max ? max : (value < min ? min : value);
}

float clamp01(float value) {
    return clamp(value, 0.f, 1.f);
}

float clampMin(float value, float min) {
    return value < min ? min : value;
}

float clampMax(float value, float max) {
    return value > max ? max : value;
}

float repeat(float value, float min, float max) {
    return value < min ? max - remainderf(min - value, max - min) : (value > max ? min + remainder(value - max, max - min) : value);
}

float repeat(float value, float length) {
    return repeat(value, 0, length);
}

float pingpong(float value, float min, float max) {
    float len = max - min;
    float rem = remainderf(value, len * 2.f);
    if (rem < 0) rem = len * 2.f + rem; // convert negative remainder to positive
    if (rem < len) return min + rem;
    else return max - (rem - len);
}

float pingpong(float value, float length) {
    return pingpong(value, 0, length);
}

float pixelate(float value, float scale) {
    float rem = remainderf(value, scale);
    if (abs(rem) < scale / 2.f) return value - rem;
    else return value - rem + scale * sign(value);
}

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}
float rescale(float value, float min1, float max1, float min2, float max2, bool invert) {
    float rel = (value - min1) / (max1 - min1);
    if (invert) rel = 1 - rel;
    return min2 + (max2 - min2) * rel;
}