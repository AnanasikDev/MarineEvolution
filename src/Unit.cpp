#include "Unit.hpp"
#include "World.hpp"
#include "AI.hpp"
#include "config.hpp"
#include "Mathf.hpp"
#include <algorithm>
#include "Random.hpp"

Unit::Unit(){
    shape = std::make_unique<sf::CircleShape>();
    shape->setPosition(position.getsf());
}

void Unit::translate(const Vectorf& delta){
    moveTo(position + delta);
}

void Unit::moveTo(const Vectorf& newPos){
    position = Vectorf(clamp(newPos.x, 0, worldWidth), clamp(newPos.y, 0, worldHeight));
    shape->setPosition(position.getsf());
}

void Unit::render(){
    World::world->window->draw(*shape);
}

void Unit::onBirth(){
    int v = pingpong(genom->encode() * 255 * 10, 0, 255);
    shape->setFillColor(sf::Color(v, v / 2.0f, v / 3.0f, 255));
    moveTo(
        Random::getVector(
            Vectorf(0, worldWidth), 
            Vectorf(0, worldHeight)
            ));
}

void Unit::printGenome() const {
    std::cout << "Genome:\n";
    for (const auto& conn : genom->connections) {
        //std::cout << "in_neuron_" << static_cast<int>(conn->in_neuron)
        //          << " -> out_neuron_" << static_cast<int>(conn->out_neuron) << "\n";
        std::cout << getNeuronName(conn->in_neuron) << "(" << static_cast<int>(conn->in_neuron) << ")" << " -> " << getNeuronName(conn->out_neuron) << "(" << static_cast<int>(conn->out_neuron) << ")" << "\n";
    }
}

bool Unit::containsPoint(const Vectorf& point) const {
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    return (dx * dx + dy * dy) <= (fishRadius * fishRadius);
}