#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "config.hpp"
#include "Time.h"
#include "AI.hpp"
#include "World.hpp"
#include "Unit.hpp"
#include "Fish.hpp"
#include "Random.hpp"

int main()
{
    World world(worldWidth, worldHeight);

    for (int i = 0; i < maxUnits; i++){
        world.allfish.push_back(std::make_unique<Fish>());
        Fish* fish = world.allfish.back().get();
        fish->moveTo(
            Random::getVector(
                Vectorf(0, world.size.x), 
                Vectorf(0, world.size.y)
                ));
        fish->genom->fillRandom();
    }

    while (world.window->isOpen()) {
		sf::Event event;
		while (world.window->pollEvent(event)){
			if (event.type == sf::Event::Closed){
                world.window->close();
            }
        }
        
        world.window->clear(sf::Color::White);

        for (int i = 0; i < maxUnits; i++){
            world.allfish[i]->update();
            world.allfish[i]->render();
        }

        if (getTime() >= genDurSecs){
            resetTime();
            gen++;
            world.nextGen();
        }

        world.window->display();
	}
	
    return 0;
}
