#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "World.hpp"
#include "Unit.hpp"
#include "Fish.hpp"
#include "Random.hpp"

constexpr int FISH_NUM = 40;

int main()
{
    World world(800, 800);

    std::vector<std::unique_ptr<Fish>> allfish;
    for (int i = 0; i < FISH_NUM; i++){
        allfish.push_back(std::make_unique<Fish>());
        allfish.back()->moveTo(
            Random::getVector(
                Vectorf(0, world.size.x), 
                Vectorf(0, world.size.y)
                ));
    }

    while (world.window->isOpen()) {
		sf::Event event;
		while (world.window->pollEvent(event)){
			if (event.type == sf::Event::Closed){
                world.window->close();
            }
        }
        
        world.window->clear(sf::Color::White);

        for (int i = 0; i < FISH_NUM; i++){
            allfish[i]->update();
            allfish[i]->render();
        }
        world.window->display();
	}
	
    return 0;
}
