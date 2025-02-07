#pragma once

#include "Vector.hpp"
#include <memory>

/// @brief Describies a unit of AI (fish, shark etc)
class Unit{
public:
    Unit();
    virtual void render();
    virtual void update() = 0;
    void translate(const Vectorf& delta);
    void moveTo(const Vectorf& newPos);
protected:
    Vectorf position;
    std::unique_ptr<sf::Shape> shape;
};