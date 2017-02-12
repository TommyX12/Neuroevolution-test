#pragma once

namespace Nebula 
{
    class FloatGene
    {
        public:
            FloatGene();
            FloatGene(float64, float64);
            static FloatGene createRandom(int, float64, float64);
            static FloatGene createChild(FloatGene&, FloatGene&, float64, float64, float64);
            static FloatGene createNextGen(FloatGene&, float64, float64);
            virtual ~FloatGene();
            std::vector<float64> data;
            float64 dataMin, dataMax;
            

        protected:

        private:
    };
}
