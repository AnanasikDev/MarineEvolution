#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector.hpp"

class World{
public:
    static World* world;
    Vectorf size;
    std::vector<std::unique_ptr<struct Fish>> allfish;

    std::unique_ptr<sf::RenderWindow> window;
    World(float width, float height);
    void nextGen();
};