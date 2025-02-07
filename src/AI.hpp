/*
Inputs:
    math:
    rand (im0)
    oscillator (im1)

    personal:
    mov direction (ip0)
    mov speed (ip1)
    pos x (ip2)
    pos y (ip3)
    dist to borders (ip4)

    social:
    num of same units around (is0)

Outputs:
    move x (o0)
    move y (o1)
    change oscillator frequency (o2)

Neutrals
    (n0)...

connection weight is a number stored as a signed integer -127 - +128, divided by 128 and shifted to be a float -1.0 - +1.0 
Connections examples:

    i0n0 w0 (00000000 00000101 10110100)
    i0n1 w1
    i3n1 w2 
    n0o0 w3
    n1o1 w4
*/

#pragma once

#include <vector>
#include <memory>

/// @brief An ordered pair of neurons and a weight
struct Connection{
    float weight;
    unsigned char in_neuron;
    unsigned char out_neuron;

    Connection() = default;
    Connection(Connection& other);

    void randomize();
    void mutate(float max01);
};

struct Genom{
    unsigned char connectionsNum;
    std::vector<std::unique_ptr<Connection>> connections;
    float oscScale;

    Genom() = default;
    Genom(Genom& other);

    void mutate(float max);
    void fillRandom();
    void inherit(const Genom& parent);
    void process(std::vector<float>& neurons);
    void sortConnections();
    float encode() const;
};
