#include "engine/includes/AI.h"

namespace Nebula
{
    NeuralNetwork::NeuralNetwork(int maxNeurons)
    {
        this->maxNeurons = maxNeurons;
        this->neurons.reserve(maxNeurons);
    }
    
    int NeuralNetwork::createNeuron(bool manualInput, float64 (*thresholdFunction)(float64, float64))
    {
        if (this->neurons.size() >= maxNeurons) return -1;
        int index = this->neurons.size();
        this->neurons.push_back(Neuron(manualInput, thresholdFunction));
        return index;
    }
    
    void NeuralNetwork::addConnection(int from, int to)
    {
        this->neurons[to].inputs.push_back(from);
        this->neurons[to].weights.push_back(0.0);
    }
    
    void NeuralNetwork::translateGene(float64* pointer)
    {
        int l = this->neurons.size();
        for (int i = 0; i < l; i++){
            this->neurons[i].result = 0.0;
            int m = this->neurons[i].weights.size();
            for (int j = 0; j < m; j++){
                this->neurons[i].weights[j] = *pointer;
                pointer++;
            }
            this->neurons[i].threshold = *pointer;
            pointer++;
        }
    }
    
    void NeuralNetwork::setInput(int neuron, float64 data)
    {
        this->neurons[neuron].result = data;
    }
    
    float64 NeuralNetwork::getOutput(int neuron)
    {
        return this->neurons[neuron].result;
    }
    
    void NeuralNetwork::process()
    {
        int l = this->neurons.size();
        for (Neuron& neuron:this->neurons){
            if (neuron.manualInput) continue;
            neuron.input = 0.0;
            int i = 0; 
            for (int inputIndex:neuron.inputs){
                neuron.input += this->neurons[inputIndex].result * neuron.weights[i];
                i++;
            }
        }
        for (Neuron& neuron:this->neurons){
            if (neuron.manualInput) continue;
            neuron.result = neuron.thresholdFunction(neuron.input, neuron.threshold);
        }
    }
    
    int NeuralNetwork::getGeneSize()
    {
        int size = 0;
        int l = this->neurons.size();
        for (int i = 0; i < l; i++){
            int m = this->neurons[i].weights.size();
            for (int j = 0; j < m; j++) size++;
            size++;
        }
        return size;
    }

    NeuralNetwork::~NeuralNetwork()
    {
        
    }
}
