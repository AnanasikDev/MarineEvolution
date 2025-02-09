#include "config.hpp"

int gen = 0;
float simSpeed = 1.0f;

std::string getNeuronName(int neuronID) {
    // static const std::unordered_map<int, std::string> neuronNames = {
    //     {in_rand, "in_rand"}, {in_oscl, "in_oscl"}, {in_mvdrx, "in_mvdrx"},
    //     {in_mvdry, "in_mvdry"}, {in_mvsp, "in_mvsp"}, {in_posx, "in_posx"},
    //     {in_posy, "in_posy"}, {in_bord, "in_bord"}, {in_pplt, "in_pplt"},
    //     {o_movx, "o_movx"}, {o_movy, "o_movy"}, {o_oscf, "o_oscf"}
    // };
    static const std::unordered_map<int, std::string> neuronNames = {
        {in_rand, "in_rand"}, {in_oscl, "in_oscl"},
        {in_posx, "in_posx"}, {in_pplt, "in_pplt"},
        {in_posy, "in_posy"}, {in_bord, "in_bord"}, {o_movx, "o_movx"}, {o_movy, "o_movy"}, {o_oscf, "o_oscf"}
    };

    auto it = neuronNames.find(neuronID);
    return (it != neuronNames.end()) ? it->second : "neutral";
}