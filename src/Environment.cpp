#include "includes/gameGlobal.h"

using namespace Nebula;

Environment::Environment()
{
    //ctor
    
}

void Environment::create()
{
    this->spaceHeld = false;
    
    this->population.create(g_maxPopulation);
    this->foods.create(g_maxFood);
    this->bullets.create(g_maxBullets);
    
    for (int i = 0; i < g_maxPopulation; i++){
        this->population[i].create();
        this->population[i].visible = false;
        this->organismContainer.addChild(this->population[i]);
    }
    this->addChild(this->organismContainer);
    
    for (int i = 0; i < g_maxFood; i++){
        this->foods[i].create();
        this->foods[i].poison = i < g_foodPoison;
        this->foods[i].visible = false;
        this->foodContainer.addChild(this->foods[i]);
    }
    this->addChild(this->foodContainer);
    
    for (int i = 0; i < g_maxBullets; i++){
        this->bullets[i].create();
        this->bullets[i].visible = false;
        this->bulletContainer.addChild(this->bullets[i]);
    }
    this->addChild(this->bulletContainer);
    
    this->generateEnv();
    
    this->framePassed = 0;
    this->averageFitness = 0.0;
    this->generation = 1;
    
    this->infoText.setFont(cur_game->defaultFont);
    this->infoText.setColor(sf::Color::White);
    this->infoText.setCharacterSize(20);
    this->infoText.setStyle(sf::Text::Bold);
    cur_game->addText(this->infoText);
}

void Environment::generateEnv()
{
    this->population.clear();
    
    this->foods.clear();
    
    this->bullets.clear();
    
    for (int i = 0; i < g_startingPopulation; i++){
        this->addOrganism();
        Organism& organism = this->population[i];
        FloatGene gene = FloatGene::createRandom(organism.brain.getGeneSize()+ai_geneExtraLength, ai_weightMin, ai_weightMax);
        organism.setGene(gene);
    }
    
    this->foodSpawnTimer = 0;
    this->randomSpawnTimer = 0;
    
    for (int i = 0; i < g_startingFood; i++){
        this->addFood();
    }
}

int Environment::addOrganism()
{ 
    int poolIndex = this->population.enableNext();
    if (poolIndex == -1) return -1;
        
    Organism& organism = this->population[poolIndex];
    organism.visible = true;
    this->resetOrganism(organism);
    
    return poolIndex;
}

void Environment::resetOrganism(Organism& organism)
{
    organism.pos.x = Util::random(0, cur_game->get_rawWidth());
    organism.pos.y = Util::random(0, cur_game->get_rawHeight());
    organism.set_rotation(Util::random(0, 360));
    organism.tile.syncedMotionBlur = false;
    organism.reset();
}

void Environment::removeOrganism(int poolIndex)
{
    this->population.disable(poolIndex);
    Organism& organism = this->population[poolIndex];
    
    organism.visible = false;
}

int Environment::addFood()
{
    int poolIndex = this->foods.enableNext();
    if (poolIndex == -1) return -1;
    
    Food& food = this->foods[poolIndex];
    food.visible = true;
    this->resetFood(food);
    
    return poolIndex;
}

void Environment::resetFood(Food& food)
{
    food.pos.x = Util::random(0, cur_game->get_rawWidth());
    food.pos.y = Util::random(0, cur_game->get_rawHeight());
    food.tile.syncedMotionBlur = false;
}

void Environment::removeFood(int poolIndex)
{
    this->foods.disable(poolIndex);
    Food& food = this->foods[poolIndex];
    
    food.visible = false;
}

int Environment::addBullet(Vec2D& pos, float64 rotation)
{
    int poolIndex = this->bullets.enableNext();
    if (poolIndex == -1) return -1;
    
    Bullet& bullet = this->bullets[poolIndex];
    bullet.visible = true;
    this->resetBullet(bullet, pos, rotation);
    
    return poolIndex;
}

void Environment::resetBullet(Bullet& bullet, Vec2D& pos, float64 rotation)
{
    bullet.reset(pos, rotation);
    bullet.tile.syncedMotionBlur = false;
}

void Environment::removeBullet(int poolIndex)
{
    this->bullets.disable(poolIndex);
    Bullet& bullet = this->bullets[poolIndex];
    
    bullet.visible = false;
}

void Environment::update()
{
    
    std::string infoStr;
    infoStr += "Press SPACE to Accelerate";
    infoStr += "\n";
    infoStr += "\n";
    if (g_generationTimer > 0) {
        infoStr += "Time Remaining to Next Generation: " + Convert::str((float64)(g_generationTimer-framePassed)/g_fps);
        infoStr += "\n";
        infoStr += "Average Fitness: " + Convert::str(this->averageFitness);
        infoStr += "\n";
        infoStr += "Generation: " + Convert::str(this->generation);
        infoStr += "\n";
    }
    this->infoText.setString(infoStr);
    
    if (!this->spaceHeld && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && cur_game->get_hasFocus()) cur_game->set_fps(cur_game->get_fps() == 60 ? 600 : 60);
    this->spaceHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    
    if (this->foodSpawnTimer > 0) this->foodSpawnTimer--;
    else {
        this->foodSpawnTimer = g_foodSpawnTimer;
        this->addFood();
    }
    
    if (this->randomSpawnTimer > 0) this->randomSpawnTimer--;
    else {
        this->randomSpawnTimer = g_randomSpawnTimer;
        
        int poolIndex = this->addOrganism();
        if (poolIndex != -1) {
            Organism& organism = this->population[poolIndex];
            FloatGene gene = FloatGene::createRandom(organism.brain.getGeneSize()+ai_geneExtraLength, ai_weightMin, ai_weightMax);
            organism.setGene(gene);
        }
    }
    
    if (g_generationTimer > 0) this->framePassed++;
    if (this->framePassed > g_generationTimer || this->population.isEmpty()){
        this->framePassed = 0;
        this->generation++;
        
        while(this->addFood() != -1);
        
        for (int i = 0; i < this->foods.get_size(); i++){
            if (this->foods.isEnabled(i)) {
                this->resetFood(this->foods[i]);
            }
        }
        
        ObjectPool<Organism> lastGen = this->population;
        
        std::vector<float64> fitness;
        fitness.reserve(lastGen.get_maxSize());
        for (int i = 0; i < lastGen.get_maxSize(); i++){
            Organism& organism = lastGen[i];
            //fitness.push_back((float64)1.0 / (1.0 + organism.foodEaten));
            fitness.push_back(std::max(0.0, organism.evaluate()));
        }
        
        ///*
        float64 totalFitness = 0.0;
        for (float64 number:fitness){
            totalFitness += number;
        }
        this->averageFitness = (float64)totalFitness / fitness.size();
        //*/
        
        while(this->addOrganism() != -1);
        
        for (int i = 0; i < this->population.get_size(); i++){
            if (this->population.isEnabled(i)) {
                Organism& organism = this->population[i];
                int parent1Index = Util::randomSelect(fitness);
                int parent2Index = Util::randomSelect(fitness);
                FloatGene gene = FloatGene::createChild(lastGen[parent1Index].gene, lastGen[parent2Index].gene, ai_mutationRate, ai_mutationDeviation, ai_crossoverRate);
                this->resetOrganism(organism);
                organism.setGene(gene);
            }
        }
    }
}

Environment::~Environment()
{
    //dtor
}
