#pragma once
#include "Vector.hpp"

// AI config
constexpr unsigned char maxInNeurons = 8;
constexpr unsigned char maxOutNeurons = 3;
constexpr unsigned char maxNeutralNeurons = 3;
constexpr unsigned char maxNeurons = maxInNeurons + maxOutNeurons + maxNeutralNeurons;
constexpr float weightMinMax = 8.0f;

// World config
constexpr int maxUnits = 30;
constexpr int worldWidth = 600;
constexpr int worldHeight = 600;
constexpr float fishRadius = 4.0f;
constexpr float genDurSecs = 10.0f;
constexpr float simSpeed = 1.0f;
extern int gen;

constexpr unsigned char in_rand = 0;
constexpr unsigned char in_oscl = 1;
constexpr unsigned char in_mvdrx = 2;
constexpr unsigned char in_mvdry = 3;
constexpr unsigned char in_mvsp = 4;
constexpr unsigned char in_posx = 5;
constexpr unsigned char in_posy = 6;
constexpr unsigned char in_bord = 7;
constexpr unsigned char in_pplt = 8;

constexpr unsigned char o_movx = 9;
constexpr unsigned char o_movy = 10;
constexpr unsigned char o_oscf = 11;