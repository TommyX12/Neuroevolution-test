#pragma once

namespace Nebula
{
    
    class NeuralNetwork
    {
        public:
            int maxNeurons;
            std::vector<Neuron> neurons;
            NeuralNetwork(int);
            virtual ~NeuralNetwork();
            
            int createNeuron(bool, float64 (*thresholdFunction)(float64, float64));
            void addConnection(int, int);
            void translateGene(float64*);
            
            void setInput(int, float64);
            void process();
            float64 getOutput(int);
            
            int getGeneSize();

        protected:

        private:
    };
}
