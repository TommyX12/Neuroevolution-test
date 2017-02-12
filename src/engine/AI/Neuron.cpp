#include "engine/includes/AI.h"

namespace Nebula 
{
    Neuron::Neuron(bool manualInput, float64 (*thresholdFunction)(float64, float64))
    {
        //ctor
        this->manualInput = manualInput;
        this->thresholdFunction = thresholdFunction;
        this->result = 0.0;
    }

    Neuron::~Neuron()
    {
        //dtor
    }
    
    float64 Neuron::stepFunction(float64 input, float64 threshold)
    {
        if (input > threshold) return 1.0;
        return 0.0;
    }
    
    float64 Neuron::sigmoidFunction(float64 input, float64 threshold)
    {
        return 2.0 / (1.0 + exp(-input / std::max(1.0, threshold))) - 1.0;
    }
    
    float64 Neuron::unsignedSigmoidFunction(float64 input, float64 threshold)
    {
        return 1.0 / (1.0 + exp(-input / std::max(1.0, threshold)));
    }
    
    float64 Neuron::fastSigmoidFunction(float64 input, float64 threshold)
    {
        return input / (std::max(1.0, threshold) + abs(input));
    }
    
    float64 Neuron::unsignedFastSigmoidFunction(float64 input, float64 threshold)
    {
        return input / (std::max(1.0, threshold) + abs(input)) * 0.5 + 0.5;
    }
}
