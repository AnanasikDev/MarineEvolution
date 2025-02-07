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

float Unit::evaluateSuccess() const{
    return (position - Vectorf(worldWidth / 2.0f, worldHeight / 2.0f)).getLength();
}