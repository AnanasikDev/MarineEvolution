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

    oscScale = parent.oscScale;
}


void Genom::mutate(float max01){
    float r = Random::getFloat();
    
    // rarely change connections number
    if (r < max01 / 6.0f){
        int d = Random::getSign();
        connectionsNum += d;
        if (d > 0)
        {
            connections.push_back(std::make_unique<Connection>());
            connections.back()->randomize();
        }
        else{
            if (!connections.empty())
                connections.pop_back();
        }
    }

    // often change connections values
    if (r < max01 / 1.2f){
        if (connections.size() != 0){
            int i = Random::getInt(0, connections.size() - 1);
            Connection* con = connections[i].get();
            con->mutate(max01);
        }
    }

    if (r > 0.7f){
        oscScale = clamp(oscScale + (Random::getFloat(-max01, max01) / 10.0f), -oscScaleMinMax, oscScaleMinMax);
    }
}

void Genom::fillRandom(){
    oscScale = Random::getFloat(-oscScaleMinMax, oscScaleMinMax);
    connectionsNum = Random::getInt(4, 11);
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
            in_neuron = clamp(Random::getInt(0, maxNeurons - 1), 0, maxNeurons - 1);
        }
        else{
            out_neuron = clamp(Random::getInt(0, maxNeurons - 1), 0, maxNeurons - 1);
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

float Genom::encode() const {
    float encoded_value = 0.0f;
    float total_weight = 0.0f;
    float total_in_neurons = 0.0f;
    float total_out_neurons = 0.0f;

    // Iterate over each connection and normalize its values
    for (const auto& conn : connections) {
        // Normalize weight: [weightMinMax, -weightMinMax] -> [0.0, 1.0]
        float normalized_weight = (conn->weight + weightMinMax) / (2 * weightMinMax);
        total_weight += normalized_weight;

        // Normalize in_neuron: [0, maxInNeurons] -> [0.0, 1.0]
        float normalized_in_neuron = static_cast<float>(conn->in_neuron) / maxInNeurons;
        total_in_neurons += normalized_in_neuron;

        // Normalize out_neuron: [0, maxOutNeurons] -> [0.0, 1.0]
        float normalized_out_neuron = static_cast<float>(conn->out_neuron) / maxOutNeurons;
        total_out_neurons += normalized_out_neuron;
    }

    // Combine the normalized values
    size_t num_connections = connections.size();
    if (num_connections > 0) {
        total_weight /= num_connections;
        total_in_neurons /= num_connections;
        total_out_neurons /= num_connections;

        // Combine the normalized averages to get a final value between 0.0 and 1.0
        encoded_value = (total_weight + total_in_neurons + total_out_neurons) / 3.0f;
    }

    return encoded_value;
}