#pragma once
#include "Vector.hpp"
#include <unordered_map>

// AI config
constexpr int maxInNeurons = 5;
constexpr int maxOutNeurons = 3;
constexpr int maxNeutralNeurons = 3;
constexpr int maxNeurons = maxInNeurons + maxOutNeurons + maxNeutralNeurons;
constexpr float weightMinMax = 8.0f;
constexpr float oscScaleMinMax = 10.0f;

// World config
constexpr int maxUnits = 300;
constexpr int worldWidth = 600;
constexpr int worldHeight = 600;
constexpr float fishRadius = 3.0f;
constexpr float genDurSecs = 4.0f;
extern float simSpeed;
constexpr float bestPortion = 0.1f;
constexpr float mutationStrength = 0.2f;
constexpr float mutationFreq = 0.5f;
extern int gen;

constexpr int in_rand = 0;
constexpr int in_oscl = 1;
//constexpr int in_mvdrx = 2;
//constexpr int in_mvdry = 3;
//constexpr int in_mvsp = 4;
constexpr int in_posx = 2;
constexpr int in_posy = 3;
constexpr int in_bord = 4;
//constexpr int in_pplt = 8;

constexpr int o_movx = 5;
constexpr int o_movy = 6;
constexpr int o_oscf = 7;

std::string getNeuronName(int neuronID);