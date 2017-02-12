#include "includes/gameGlobal.h"

using namespace Nebula;

Game* cur_game = nullptr;
float64 ai_weightMin = -4;
float64 ai_weightMax = 4;
float64 ai_inputMapMin = -8;
float64 ai_inputMapMax = 8;
int ai_maxNeurons = 128;
int ai_hiddenNeurons = 32;
bool ai_recurrence = true;
float64 ai_mutationRate = 0.05;
float64 ai_mutationDeviation = 1;
float64 ai_crossoverRate = 0.2;
int ai_geneExtraLength = 1;
int ai_geneIndexColor = 0;
int g_maxPopulation = 28;
int g_maxFood = 32;
int g_maxBullets = 128;
int g_startingPopulation = 28;
int g_startingFood = 32;
int g_fps = 60;
int g_foodPoison = 12;
int g_generationTimer = 30 * g_fps;
int g_foodSpawnTimer = 0.3 * g_fps;
int g_randomSpawnTimer = 15 * g_fps;
float64 g_foodScale = 0.175;
float64 org_fov = 90;
float64 org_scale = 0.2;
float64 org_energyIndicatorScale = 0.1;
float64 org_maxSpeed = 2.0;
int org_decomposeTimer = 10 * g_fps;
int org_replicateCooldown = 5 * g_fps;
int org_fireRate = 0.5 * g_fps;
bool org_allowFire = true;
bool org_allowDeath = true;
bool org_inputExtraInfo = true;
float64 org_maxEnergy = 100.0;
float64 org_startingEnergy = 50.0;
float64 org_foodCollisionRadius = 10;
float64 org_bulletCollisionRadius = 10;
float64 org_corpseCollisionRadius = 15;
float64 org_energyFood = 25.0;
float64 org_energyCorpse = 75.0;
float64 org_energyFire = -2.5;
float64 org_energyBulletDamage = -25.0; //obsolete
float64 org_energyReplicate = -5.0;
float64 org_energyIdlePS = -2.0 / (float64)g_fps;
float64 org_energyThrustPS = -1.0 / (float64)g_fps;
float64 org_energyTurnPS = -0.1 / (float64)g_fps;
float64 b_startingVel = 10;
float64 b_screenBoundMargin = 50;
float64 b_firePosBias = 20;
float64 b_friction = 0.9;

Game::Game()
 : NebulaGame(640, 640, "Nebula Engine", g_fps) //super constructor call
{
    cur_game = this;
    
    std::string mode = "simple manual";
    
    if (mode == "simple manual"){
        g_foodSpawnTimer = 0;
        org_allowDeath = false;
        org_allowFire = false;
        org_inputExtraInfo = false;
        //ai_recurrence = false;
        //ai_hiddenNeurons = 20;
        org_decomposeTimer = -1;
    }
    else if (mode == "simple dynamic"){
        g_generationTimer = 0;
        org_allowDeath = true;
        org_allowFire = false;
        org_inputExtraInfo = false;
        //ai_recurrence = false;
        //ai_hiddenNeurons = 20;
        org_decomposeTimer = -1;
    }
    else if (mode == "full manual"){
        g_foodSpawnTimer = 0;
        org_decomposeTimer = -1;
    }
    else if (mode == "full dynamic"){
        g_generationTimer = 0;
    }
    
    
    this->pauseOnFocusLoss = false;     
}

void Game::create()
{
    this->shapesAtlas.loadFromFile("textures/shapes.png");
    this->shapesAtlas.addTileData("circle", Rectangle(0,0,64,64));
    this->shapesAtlas.addTileData("triangle", Rectangle(64,0,64,64));
    this->shapesAtlas.addTileData("square", Rectangle(128,0,64,64));
    
    this->mainLayer.create(this->shapesAtlas);
    this->mainLayer.motionBlur = true;
    this->addLayer(this->mainLayer);
    
    this->env.create();
    
    this->mainLayer.addChild(this->env);
}

Game::~Game()
{
    //dtor
}
