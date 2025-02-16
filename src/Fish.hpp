#pragma once
#include "Unit.hpp"

class Fish : public Unit{
public:
    Fish();
    static Fish* instantiate_random();
    float evaluateSuccess() const override;
    float distanceToNearest() const override;

    void update() override;
};