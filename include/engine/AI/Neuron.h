#pragma once
namespace Nebula 
{
    class Neuron
    {
        public:
            Neuron(bool, float64 (*thresholdFunction)(float64, float64));
            virtual ~Neuron();
            std::vector<float64> weights;
            std::vector<int> inputs;
            float64 input, result;
            float64 (*thresholdFunction)(float64, float64);
            float64 threshold;
            
            bool manualInput;
            
            static float64 stepFunction(float64, float64);
            static float64 sigmoidFunction(float64, float64);
            static float64 unsignedSigmoidFunction(float64, float64);
            static float64 fastSigmoidFunction(float64, float64);
            static float64 unsignedFastSigmoidFunction(float64, float64);

        protected:

        private:
    };
}
