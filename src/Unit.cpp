#include "Unit.hpp"
#include "World.hpp"
#include "AI.hpp"
#include "config.hpp"
#include "Mathf.hpp"

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
}