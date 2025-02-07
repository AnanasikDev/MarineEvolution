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

    while (world.window->isOpen()) {
		sf::Event event;
		while (world.window->pollEvent(event)){
			if (event.type == sf::Event::Closed){
                world.window->close();
            }
        }
        
        world.window->clear(sf::Color::White);
        computeTime();

        for (int i = 0; i < maxUnits; i++){
            world.allfish[i]->update();
            world.allfish[i]->render();
        }
        
        if (elapsedTimeScaled >= genDurSecs){
            resetTime();
            gen++;
            world.nextGen();
        }

        world.window->display();
	}
	
    return 0;
}
