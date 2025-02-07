#include "AI.hpp"
#include "Random.hpp"
#include "Mathf.hpp"
#include "config.hpp"

Connection::Connection(Connection& other){
    weight = other.weight;
    in_neuron = other.in_neuron;
    out_neuron = other.out_neuron;
}

Genom::Genom(Genom& other){
    inherit(other);
}

void Genom::inherit(const Genom& parent) {
    connectionsNum = parent.connectionsNum;
    connections.clear();
    for (const std::unique_ptr<Connection>& conn : parent.connections) {
        connections.push_back(std::make_unique<Connection>(*conn));
    }

    threatDistance = parent.threatDistance;
}


Genom Genom::mutate(float max01){
    float r = Random::getFloat();
    
    // rarely change connections number
    if (r > 0.8f){
        int d = Random::getSign();
        connectionsNum += d;
        if (d > 0)
        {
            connections.push_back(std::make_unique<Connection>());
            connections.back()->randomize();
        }
        else{
            connections.pop_back();
        }
    }

    // often change connections values
    if (r > 0.35f){
        Connection* con = connections[Random::getInt(0, connections.size() - 1)].get();
        con->mutate(max01);
    }

    // sometimes change threat distance
    if (r > 0.5f){
        threatDistance = clamp(threatDistance + (Random::getFloat(-max01, max01)), 0.0f, 30.0f);
    }
}

void Genom::fillRandom(){
    threatDistance = Random::getFloat(0.0f, 10.0f);
    connectionsNum = Random::getInt(0, 10);
    connections.clear();
    for (int c = 0; c < connectionsNum; c++){
        connections.push_back(std::make_unique<Connection>());
        connections.back()->randomize();
    }
}

void Connection::randomize(){
    weight = Random::getFloat(-weightMinMax, weightMinMax);
    in_neuron = Random::getInt(0, maxNeurons - 1);
    out_neuron = Random::getInt(0, maxNeurons - 1);
}

void Connection::mutate(float max01){
    weight = clamp(weight + (Random::getFloat(-max01, max01)), -weightMinMax, weightMinMax);
    if (Random::getFloat() < max01){
        if (Random::getFloat() > 0.5f){
            in_neuron = Random::getInt(0, maxNeurons);
        }
        else{
            out_neuron = Random::getInt(0, maxNeurons);
        }
    }
}

void Genom::sortConnections() {
    std::sort(connections.begin(), connections.end(), [](const std::unique_ptr<Connection>& a, const std::unique_ptr<Connection>& b) {
        return a->in_neuron < b->in_neuron;
    });
}

void Genom::process(std::vector<float>& neurons) {
    for (const auto& connection : connections) {
        float input_value = neurons[connection->in_neuron];
        neurons[connection->out_neuron] += input_value * connection->weight; 
    }

    for (size_t i = maxInNeurons; i < neurons.size(); i++) {
        neurons[i] = std::tanh(neurons[i]);
    }
}