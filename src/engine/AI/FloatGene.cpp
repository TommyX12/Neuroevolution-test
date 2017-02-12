#include "engine/includes/AI.h"

namespace Nebula 
{
    FloatGene::FloatGene()
    {
        //ctor
    }
    
    FloatGene::FloatGene(float64 dataMin, float64 dataMax)
    {
        //ctor
        this->dataMin = dataMin;
        this->dataMax = dataMax;
    }

    FloatGene::~FloatGene()
    {
        //dtor
    }

    FloatGene FloatGene::createRandom(int length, float64 dataMin, float64 dataMax)
    {
        FloatGene newGene(dataMin, dataMax);
        for (int i = 0; i < length; i++){
            newGene.data.push_back(Util::random(dataMin, dataMax));
        }
        return newGene;
    }
    
    FloatGene FloatGene::createChild(FloatGene& parent1, FloatGene& parent2, float64 mutationRate, float64 mutationDeviation, float64 crossoverRate)
    {
        if (Util::random(0.0, 1.0) >= crossoverRate) {
            if (Util::random(0.0, 1.0) < 0.5) return createNextGen(parent1, mutationRate, mutationDeviation);
            else return createNextGen(parent2, mutationRate, mutationDeviation);
        }
        float64 dataMin = parent1.dataMin;
        float64 dataMax = parent1.dataMax;
        FloatGene newGene(dataMin, dataMax);
        int l = parent1.data.size();
        int mid = Util::randomInt(0, l+1);
        FloatGene* source1 = Util::randomInt(0, 2) ? &parent1 : &parent2;
        FloatGene* source2 = source1 == &parent2 ? &parent1 : &parent2;
        for (int i = 0; i < mid; i++){
            newGene.data.push_back(source1->data[i]);
            if (Util::random(0.0, 1.0) < mutationRate) newGene.data[i] = Util::clamp(Util::randomGaussian(newGene.data[i], mutationDeviation), dataMin, dataMax);
        }
        for (int i = mid; i < l; i++){
            newGene.data.push_back(source2->data[i]);
            if (Util::random(0.0, 1.0) < mutationRate) newGene.data[i] = Util::clamp(Util::randomGaussian(newGene.data[i], mutationDeviation), dataMin, dataMax);
        }
        return newGene;
    }
    
    FloatGene FloatGene::createNextGen(FloatGene& parent, float64 mutationRate, float64 mutationDeviation)
    {
        float64 dataMin = parent.dataMin;
        float64 dataMax = parent.dataMax;
        FloatGene newGene(dataMin, dataMax);
        int l = parent.data.size();
        for (int i = 0; i < l; i++){
            newGene.data.push_back(parent.data[i]);
            if (Util::random(0.0, 1.0) < mutationRate) newGene.data[i] = Util::clamp(Util::randomGaussian(newGene.data[i], mutationDeviation), dataMin, dataMax);
        }
        return newGene;
    }
}
