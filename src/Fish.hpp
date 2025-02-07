#pragma once
#include "Unit.hpp"

class Fish : public Unit{
public:
    Fish();
    static Fish* instantiate_random();

    void update() override;
};