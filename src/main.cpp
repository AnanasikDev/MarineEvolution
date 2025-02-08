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

float inputDelay = 0.2f;
float lastInput = 0;

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

        if (elapsedTimeAbsolute - lastInput > inputDelay){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                simSpeed *= 2.0f;
                std::cout << "Simulation speed increased from " << simSpeed / 2.0f << " to " << simSpeed << "\n";
                lastInput = elapsedTimeAbsolute;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                simSpeed /= 2.0f;
                std::cout << "Simulation speed decreased from " << simSpeed * 2.0f << " to " << simSpeed << "\n";
                lastInput = elapsedTimeAbsolute;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if (simSpeed == 0){
                    simSpeed = 1.0f;
                    std::cout << "Simulation unpaused\n";
                }
                else{
                    simSpeed = 0.0f;
                    std::cout << "Simulation paused\n";
                }
                lastInput = elapsedTimeAbsolute;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                Vectorf mousePos = Vectorf(event.mouseButton.x, event.mouseButton.y);
                // Check which unit was clicked
                for (const auto& unit : world.allfish) {
                    if (unit->containsPoint(mousePos)) {
                        unit->printGenome(); // Print genome in console
                        break; // Stop checking after first hit
                    }
                }
                lastInput = elapsedTimeAbsolute;
            }
        }

        for (int i = 0; i < maxUnits; i++){
            world.allfish[i]->update();
            world.allfish[i]->render();
        }

        if (genElapsedTimeScaled >= genDurSecs){
            gen++;
            world.nextGen();
            resetGenTime();
        }

        world.window->display();
	}
	
    return 0;
}
