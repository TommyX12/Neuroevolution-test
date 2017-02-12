#pragma once


class Bullet: public Nebula::AtlasContainer
{
    public:
        Bullet();
        
        int poolIndex;
        
        virtual ~Bullet();
        
        void create();
        void reset(Nebula::Vec2D&, Nebula::float64);
        
        void update();
        
        Nebula::AtlasEntity tile;

    protected:

    private:
};

