#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>

template <typename T>
class Vector {

public:
    T x;
    T y;

    static const Vector zero;
    static const Vector half;
    static const Vector one;
    static const Vector up;
    static const Vector down;
    static const Vector right;
    static const Vector left;

    static const float eps;

    Vector() : x(0), y(0) {}

    Vector(T _x, T _y) : x(_x), y(_y) {
    }

    Vector(sf::Vector2<T> sfother) {
        this->x = sfother.x;
        this->y = sfother.y;
    }

    Vector<T>& operator=(const Vector<T>& other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    bool operator==(const Vector<T>& other) const {
        return abs(this->x - other.x) < eps && abs(this->y - other.y) < eps;
    }

    bool operator!=(const Vector<T>& other) const {
        return this->x != other.x || this->y != other.y;
    }

    Vector<T>& operator+=(const Vector<T>& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector<T>& operator*=(const float other) {
        this->x *= other;
        this->y *= other;
        return *this;
    }

    Vector<T>& operator-=(const Vector<T>& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vector<T>& operator/=(const float other) {
        this->x /= other;
        this->y /= other;
        return *this;
    }

    Vector<T> operator+(Vector<T> other) const {
        return Vector<T>(this->x + other.x, this->y + other.y);
    }

    Vector<T> operator-(Vector<T> other) const {
        return Vector<T>(this->x - other.x, this->y - other.y);
    }

    Vector<T> operator*(T fac) const {
        return Vector<T>(this->x * fac, this->y * fac);
    }

    Vector<T> operator/(T fac) const {
        return Vector<T>(this->x / fac, this->y / fac);
    }

    Vector<T> operator*(const Vector<T> other) const {
        return Vector<T>(this->x * other.x, this->y * other.y);
    }

    Vector<T> operator/(const Vector<T> other) const {
        return Vector<T>(this->x / other.x, this->y / other.y);
    }

    Vector<T> operator-() const {
        return Vector<T>(-this->x, -this->y);
    }

    T dotProduct(const Vector<T> other) const {
        return this->x * other.x + this->y * other.y;
    }

    T crossProduct(const Vector<T> other) const {
        return this->x * other.y - this->y * other.x;
    }

    sf::Vector2<T> getsf() const {
        return sf::Vector2<T>(this->x, this->y);
    }

    float getLength() const {
        return sqrtf(x * x + y * y);
    }

    Vector<T> normalized() const {
        float m = getLength();
        if (m == 0)
            return Vector<T>();
        return Vector<T>(x / m, y / m);
    }

    Vector<T> clampMagnitude(float min, float max) const {
        float m = getLength();
        if (m == 0)
            return *this;
        if (m < min)
            return Vector<T>(x * min / m, y * min / m);
        if (m > max)
            return Vector<T>(x * max / m, y * max / m);
        return *this;
    }

    Vector<T> vabs() const {
        return Vector<T>(abs(x), abs(y));
    }

    float distance(Vector<T> other) const {
        return Vector<T>(x - other.x, y - other.y).getLength();
    }

    std::string toStr() const {
        char buff[50];
        //sprintf_s(buff, 50, "(%.4f, %.4f)", (float)(this->x), (float)(this->y));
        return buff;
    }

    static Vector<T> fromsf(sf::Vector2<T> sfvec) {
        return Vector<T>(sfvec.x, sfvec.y);
    }

    template <typename From, typename To>
    static Vector<To> otherFromsf(sf::Vector2<From> sfvec) {
        return Vector<To>(To(sfvec.x), To(sfvec.y));
    }

    template <typename R>
    Vector<R> to() {
        return Vector<R>(R(x), R(y));
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    return os << "Vector(" << vec.x << ", " << vec.y << ")";
}

template <typename T>
const float Vector<T>::eps = 10e-6f;

template <typename T>
const Vector<T> Vector<T>::zero = Vector<T>(0, 0);

template <typename T>
const Vector<T> Vector<T>::half = Vector<T>(0.5f, 0.5f);

template <typename T>
const Vector<T> Vector<T>::one = Vector<T>(1, 1);

template <typename T>
const Vector<T> Vector<T>::up = Vector<T>(0, -1);

template <typename T>
const Vector<T> Vector<T>::down = Vector<T>(0, 1);

template <typename T>
const Vector<T> Vector<T>::right = Vector<T>(1, 0);

template <typename T>
const Vector<T> Vector<T>::left = Vector<T>(-1, 0);

using Vectorf = Vector<float>;
using Vectori = Vector<int>;