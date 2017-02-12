#pragma once

class Organism: public Nebula::AtlasContainer
{
    public:
        Organism();
        
        int poolIndex;
        
        Nebula::FloatGene gene;
        
        void create();
        void reset();
        void setGene(Nebula::FloatGene&);
        int brainInputs[9], brainOutputs[5];
        virtual ~Organism();
        Nebula::AtlasEntity tile, energyIndicator;
        void update();
        int foodEaten, poisonEaten, corpseEaten;
        
        Nebula::float64 evaluate();
        
        void replicate();
        void fire(Nebula::float64);
        
        Nebula::float64 color;
        
        bool alive;
        int decomposeTimer, replicateCooldown, fireTimer;
        
        Nebula::float64 energy;
        
        Nebula::NeuralNetwork brain;

    protected:

    private:
};
