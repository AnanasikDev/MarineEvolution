#include "config.hpp"
#include "World.hpp"
#include "Time.h"
#include "AI.hpp"
#include "Random.hpp"
#include "Unit.hpp"
#include "Fish.hpp"

World* World::world = nullptr; 

World::World(float width, float height){
    world = this;
    size = Vectorf(width, height);
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Evolution");
    resetTime();

    for (int i = 0; i < maxUnits; i++){
        allfish.push_back(std::make_unique<Fish>());
        Fish* fish = allfish.back().get();
        fish->moveTo(
            Random::getVector(
                Vectorf(0, size.x), 
                Vectorf(0, size.y)
                ));
        fish->genom->fillRandom();
        fish->onBirth();
    }
}

void World::nextGen() {
    if (allfish.empty()){
        std::cout << "Allfish is empty\n";
        return;
    }
    std::cout << "Generation " << gen << "\n";

    // Evaluate success (replace with actual success criteria)
    std::vector<std::pair<Fish*, float>> scoredUnits;
    for (int f = 0; f < maxUnits; f++) {
        float score = allfish[f]->evaluateSuccess(); // Assume this function exists in Unit
        scoredUnits.emplace_back(allfish[f].get(), score);
    }

    // Sort by success score (higher is better)
    std::sort(scoredUnits.begin(), scoredUnits.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Determine top performers (e.g., top 20%)
    int numToKeep = std::max(1, static_cast<int>(allfish.size() * bestPortion));

    // Select the best genomes
    std::vector<Genom*> bestGenomes;
    for (int i = 0; i < numToKeep; i++) {
        bestGenomes.push_back(scoredUnits[i].first->genom.get());
    }

    // Make the rest inherit with mutations
    for (size_t i = numToKeep; i < scoredUnits.size(); i++) {
        Genom* parentGenom = bestGenomes[Random::getInt(0, bestGenomes.size() - 1)]; // Random top parent
        scoredUnits[i].first->genom->inherit(*parentGenom);
        if (Random::getFloat() < mutationFreq){
            scoredUnits[i].first->genom->mutate(mutationStrength);
        }
        scoredUnits[i].first->onBirth();
    }
}
