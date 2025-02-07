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
    float evaluateSuccess() const;
    
protected:
    Vectorf position;
    Vectorf lastPosition;
    Vectorf velocity;
    std::unique_ptr<sf::Shape> shape;
};