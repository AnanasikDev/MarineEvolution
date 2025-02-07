#include "Fish.hpp"
#include <iostream>

Fish::Fish() : Unit(){
    sf::CircleShape* circle = static_cast<sf::CircleShape*>(shape.get());
    float r = 4.0f;
    circle->setRadius(r);
    shape->setOrigin(Vectorf::half.getsf() * r);
    circle->setFillColor(sf::Color::Blue);
}

void Fish::update(){
    
}