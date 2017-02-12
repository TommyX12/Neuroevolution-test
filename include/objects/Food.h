#pragma once


class Food: public Nebula::AtlasContainer
{
    public:
        Food();
        
        int poolIndex;
        
        bool poison;
        
        void create();
        Nebula::AtlasEntity tile;
        void update();
        virtual ~Food();

    protected:

    private:
};
