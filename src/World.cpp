#include "World.hpp"

World* World::world = nullptr; 

World::World(float width, float height){
    world = this;
    size = Vectorf(width, height);
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Evolution");
}