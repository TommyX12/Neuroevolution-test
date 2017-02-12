#pragma once

class Game : public Nebula::NebulaGame
{
    public:
        Game();
        void create();
        virtual ~Game();
        Nebula::AtlasDisplay mainLayer;
        Nebula::TextureAtlas shapesAtlas;
        Environment env;
        
    protected:
    private:
};

extern Game* cur_game;
extern Nebula::float64 ai_weightMin;
extern Nebula::float64 ai_weightMax;
extern Nebula::float64 ai_inputMapMin;
extern Nebula::float64 ai_inputMapMax;
extern int ai_maxNeurons;
extern int ai_hiddenNeurons;
extern bool ai_recurrence;
extern Nebula::float64 ai_mutationRate;
extern Nebula::float64 ai_mutationDeviation;
extern Nebula::float64 ai_crossoverRate;
extern int ai_geneExtraLength;
extern int ai_geneIndexColor;
extern int g_maxPopulation;
extern int g_maxFood;
extern int g_maxBullets;
extern int g_startingPopulation;
extern int g_startingFood;
extern int g_foodPoison;
extern int g_fps;
extern int g_generationTimer;
extern int g_foodSpawnTimer;
extern int g_randomSpawnTimer;
extern Nebula::float64 g_foodScale;
extern Nebula::float64 org_fov;
extern Nebula::float64 org_scale;
extern Nebula::float64 org_energyIndicatorScale;
extern Nebula::float64 org_maxSpeed;
extern int org_decomposeTimer;
extern int org_replicateCooldown;
extern int org_fireRate;
extern bool org_allowFire;
extern bool org_allowDeath;
extern bool org_inputExtraInfo;
extern Nebula::float64 org_maxEnergy;
extern Nebula::float64 org_startingEnergy;
extern Nebula::float64 org_foodCollisionRadius;
extern Nebula::float64 org_bulletCollisionRadius;
extern Nebula::float64 org_corpseCollisionRadius;
extern Nebula::float64 org_energyFood;
extern Nebula::float64 org_energyCorpse;
extern Nebula::float64 org_energyFire;
extern Nebula::float64 org_energyBulletDamage;
extern Nebula::float64 org_energyReplicate;
extern Nebula::float64 org_energyIdlePS;
extern Nebula::float64 org_energyThrustPS;
extern Nebula::float64 org_energyTurnPS;
extern Nebula::float64 b_startingVel;
extern Nebula::float64 b_screenBoundMargin;
extern Nebula::float64 b_firePosBias;
extern Nebula::float64 b_friction;
