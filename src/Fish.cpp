#include "Fish.hpp"
#include "AI.hpp"
#include <iostream>
#include "config.hpp"
#include "World.hpp"
#include "Random.hpp"
#include "Time.h"
#include <math.h>

Fish::Fish() : Unit(){
    sf::CircleShape* circle = static_cast<sf::CircleShape*>(shape.get());
    float r = 4.0f;
    circle->setRadius(r);
    shape->setOrigin(Vectorf::half.getsf() * r);
    circle->setFillColor(sf::Color::Blue);
    genom = std::make_unique<Genom>();
}

void Fish::update() {
    std::vector<float> neurons(maxNeurons, 0.0f); // Storage for neuron activations

    // Initialize input neurons (example values, should be based on real data)
    neurons[in_rand] = (Random::getFloat() - 0.5f) * 2.0f;
    neurons[in_oscl] = sinf(elapsedTimeScaled * genom->oscScale);
    neurons[in_mvdrx] = velocity.normalized().x;
    neurons[in_mvdry] = velocity.normalized().y;
    neurons[in_mvsp] = velocity.getLength();
    neurons[in_posx] = position.x / (float)worldWidth;
    neurons[in_posy] = position.y / (float)worldHeight;
    neurons[in_bord] = std::min(
        std::min(position.x, worldWidth - position.x) / (float)worldWidth,
        std::min(position.y, worldHeight - position.y) / (float)worldHeight);
    neurons[in_pplt] = 0;

    // Process the neural network
    genom->process(neurons);

    // Apply outputs
    Vectorf move(neurons[o_movx] * simSpeed, neurons[o_movy] * simSpeed);
    lastPosition = position;
    translate(move);
    velocity = position - lastPosition;
}


Fish* Fish::instantiate_random(){
    World::world->allfish.push_back(std::make_unique<Fish>());
}

float Fish::evaluateSuccess() const {
    //return worldWidth - abs(position.x - (float)worldWidth / 2.0f);
    return -(position - Vectorf(worldWidth / 2.0f, worldHeight / 2.0f)).getLength();
}