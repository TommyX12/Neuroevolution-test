#pragma once

class Environment: public Nebula::AtlasContainer
{
    public:
        Environment();
        void create();
        void generateEnv();
        int addOrganism();
        void resetOrganism(Organism&);
        void removeOrganism(int);
        int addFood();
        void resetFood(Food&);
        void removeFood(int);
        int addBullet(Nebula::Vec2D&, Nebula::float64);
        void resetBullet(Bullet&, Nebula::Vec2D&, Nebula::float64);
        void removeBullet(int);
        virtual ~Environment();
        
        bool spaceHeld;
        
        int framePassed, generation, foodSpawnTimer, randomSpawnTimer;
        
        void update();
        
        Nebula::float64 averageFitness;
        
        Nebula::ObjectPool<Food> foods;
        Nebula::ObjectPool<Organism> population;
        Nebula::ObjectPool<Bullet> bullets;
        
        AtlasContainer foodContainer;
        AtlasContainer organismContainer;
        AtlasContainer bulletContainer;
        
        
        sf::Text infoText;
        
        int maxPopulation, maxFood, maxBullets;

    protected:

    private:
};
