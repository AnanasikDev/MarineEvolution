#include "Unit.hpp"
#include "World.hpp"

Unit::Unit(){
    shape = std::make_unique<sf::CircleShape>();
    shape->setPosition(position.getsf());
}

void Unit::translate(const Vectorf& delta){
    position += delta;
    shape->setPosition(position.getsf());
}

void Unit::moveTo(const Vectorf& newPos){
    position = newPos;
    shape->setPosition(position.getsf());
}

void Unit::render(){
    World::world->window->draw(*shape);
}