#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Vector.hpp"

class World{
public:
    static World* world;
    Vectorf size;

    std::unique_ptr<sf::RenderWindow> window;
    World(float width, float height);
};