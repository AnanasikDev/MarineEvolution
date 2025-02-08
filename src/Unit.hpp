#pragma once

#include "Vector.hpp"
#include <memory>

/// @brief Describies a unit of AI (fish, shark etc)
class Unit{
public:
    std::unique_ptr<struct Genom> genom;
    Unit();
    virtual void render();
    virtual void update() = 0;
    void translate(const Vectorf& delta);
    void moveTo(const Vectorf& newPos);
    virtual float evaluateSuccess() const = 0;
    virtual void onBirth(); 
    virtual float distanceToNearest() const = 0;
    void printGenome() const;
    bool containsPoint(const Vectorf& point) const;
    Vectorf position;
    Vectorf lastPosition;
    Vectorf velocity;
    std::unique_ptr<sf::Shape> shape;
};