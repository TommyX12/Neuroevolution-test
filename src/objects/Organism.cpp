#include "includes/objects.h"
#include "includes/gameGlobal.h"

using namespace Nebula;

Organism::Organism()
: brain(ai_maxNeurons)
{
    //ctor
}

void Organism::create()
{
    this->reset();
    
    this->tile.create(cur_game->shapesAtlas, "triangle");
    this->addChild(this->tile);
    this->tile.pos.x = 2.5;
    this->tile.set_scale(org_scale);
    
    this->energyIndicator.create(cur_game->shapesAtlas, "circle");
    this->addChild(this->energyIndicator);
    this->energyIndicator.set_scale(org_energyIndicatorScale);
    
    this->brainInputs[0] = this->brain.createNeuron(true, nullptr);//energy
    this->brainInputs[1] = this->brain.createNeuron(true, nullptr);//angle to food
    this->brainInputs[2] = this->brain.createNeuron(true, nullptr);//dist to food
    this->brainInputs[3] = this->brain.createNeuron(true, nullptr);//food is poison
    this->brainInputs[4] = this->brain.createNeuron(true, nullptr);//food detected
    this->brainInputs[5] = this->brain.createNeuron(true, nullptr);//angle to organism
    this->brainInputs[6] = this->brain.createNeuron(true, nullptr);//dist to organism
    this->brainInputs[7] = this->brain.createNeuron(true, nullptr);//organism color
    this->brainInputs[8] = this->brain.createNeuron(true, nullptr);//organism alive
    
    this->brainOutputs[0] = this->brain.createNeuron(false, Neuron::fastSigmoidFunction); //thrust
    this->brainOutputs[1] = this->brain.createNeuron(false, Neuron::fastSigmoidFunction); //turn
    this->brainOutputs[2] = this->brain.createNeuron(false, Neuron::stepFunction); //replicate
    this->brainOutputs[3] = this->brain.createNeuron(false, Neuron::stepFunction); //fire
    this->brainOutputs[4] = this->brain.createNeuron(false, Neuron::fastSigmoidFunction); //fire angle
    
    int* hiddenNeurons = new int[ai_hiddenNeurons];
    
    for (int i = 0; i < ai_hiddenNeurons; i++){
        hiddenNeurons[i] = this->brain.createNeuron(false, Neuron::stepFunction);
        ///*
        for (int j = 0; j < i; j++){
            if (ai_recurrence){
                this->brain.addConnection(hiddenNeurons[i], hiddenNeurons[j]);
                this->brain.addConnection(hiddenNeurons[j], hiddenNeurons[i]);
            }
        }
        //*/
        this->brain.addConnection(this->brainInputs[0], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[1], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[2], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[3], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[4], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[5], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[6], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[7], hiddenNeurons[i]);
        this->brain.addConnection(this->brainInputs[8], hiddenNeurons[i]);
        this->brain.addConnection(hiddenNeurons[i], this->brainOutputs[0]);
        this->brain.addConnection(hiddenNeurons[i], this->brainOutputs[1]);
        this->brain.addConnection(hiddenNeurons[i], this->brainOutputs[2]);
        this->brain.addConnection(hiddenNeurons[i], this->brainOutputs[3]);
        this->brain.addConnection(hiddenNeurons[i], this->brainOutputs[4]);
    }
    
    delete[] hiddenNeurons;
}

void Organism::reset()
{   
    this->foodEaten = this->poisonEaten = this->corpseEaten = 0;
    this->energy = org_startingEnergy;
    this->alive = true;
    this->decomposeTimer = org_decomposeTimer;
    this->replicateCooldown = org_replicateCooldown;
    this->fireTimer = 0;
}

void Organism::setGene(FloatGene& gene)
{
    this->gene = gene;
    this->brain.translateGene(&gene.data[ai_geneExtraLength]);
    this->color = Util::map(this->gene.data[ai_geneIndexColor], ai_weightMin, ai_weightMax, 0.0, 1.0);
}


Organism::~Organism()
{
    //dtor
}

void Organism::replicate()
{
    int poolIndex = cur_game->env.addOrganism();
    if (poolIndex != -1){
        this->replicateCooldown = org_replicateCooldown;
        this->energy += org_energyReplicate;
        
        Organism& organism = cur_game->env.population[poolIndex];
        cur_game->env.resetOrganism(organism);
        
        organism.energy = std::min(organism.energy, this->energy);
        
        /*
        ObjectPool<Organism> lastGen = cur_game->env.population;
        
        std::vector<float64> fitness;
        fitness.reserve(lastGen.get_maxSize());
        for (int i = 0; i < lastGen.get_maxSize(); i++){
            Organism& organism = lastGen[i];
            fitness.push_back(std::max(0.0, organism.evaluate()));
        }
        
        int parent2Index = Util::randomSelect(fitness);
        FloatGene gene = FloatGene::createChild(this->gene, lastGen[parent2Index].gene, ai_mutationRate, ai_mutationDeviation, ai_crossoverRate);
        organism.setGene(gene);
        */
        
        organism.pos = this->pos;
        organism.set_rotation(this->get_rotation());
        
        FloatGene gene = FloatGene::createNextGen(this->gene, ai_mutationRate, ai_mutationDeviation);
        organism.setGene(gene);
    }
}

void Organism::fire(float64 direction)
{
    float64 absAngle = this->get_rotation() + direction;
    Vec2D bulletPos = this->pos + Vec2D().addDirectional(b_firePosBias, absAngle);
    int poolIndex = cur_game->env.addBullet(bulletPos, absAngle);
    if (poolIndex != -1){
        this->fireTimer = org_fireRate;
        this->energy += org_energyFire;
    }
}

float64 Organism::evaluate()
{
    int x = std::max(0.0, 10.0 + this->foodEaten - 5.0 * this->poisonEaten + 2.5 * this->corpseEaten);
    //printf("%d\n", x);
    return x * x;
}

void Organism::update()
{
    if (this->alive){
        if (this->replicateCooldown > 0) this->replicateCooldown--;
        if (this->fireTimer > 0) this->fireTimer--;
        
        if (org_inputExtraInfo) this->brain.setInput(this->brainInputs[0], Util::map(this->energy / org_maxEnergy, 0.0, 1.0, 0.0, ai_inputMapMax));
        
        float64 minAngle = 0.0, minDist = std::numeric_limits<float64>::infinity();
        
        bool isPoison = false;
        bool foodDetected = false;
        
        for (int i = 0; i < cur_game->env.foods.get_size(); i++){
            if (cur_game->env.foods.isEnabled(i)){
                Food& food = cur_game->env.foods[i];
                float64 angle = Util::rotationDistance(this->get_rotation(), this->pos.angleTo(food.pos));
                if (std::abs(angle) <= org_fov * 0.5) {
                    foodDetected = true;
                    float64 dist = food.pos.distanceSq(this->pos);
                    if (dist <= minDist) {
                        minAngle = angle;
                        minDist = dist;
                        isPoison = food.poison;
                    }
                }
            }
        }
        
        
        ///*
        this->brain.setInput(this->brainInputs[1], Util::map(minAngle, -180.0, 180.0, ai_inputMapMin, ai_inputMapMax));
        this->brain.setInput(this->brainInputs[2], Util::map(Util::clamp(1.0 / std::sqrt(minDist), 0.0, 1.0), 0.0, 1.0, 0.0, ai_inputMapMax));
        this->brain.setInput(this->brainInputs[3], isPoison ? ai_inputMapMax : 0.0);
        this->brain.setInput(this->brainInputs[4], !foodDetected ? ai_inputMapMax : 0.0);
        
        /*
        bool isPoison = false;
        //bool foodDetected = false;
        
        for (int i = 0; i < cur_game->env.foods.get_size(); i++){
            if (cur_game->env.foods.isEnabled(i)){
                Food& food = cur_game->env.foods[i];
                float64 angle = Util::rotationDistance(this->get_rotation(), this->pos.angleTo(food.pos));
                //if (std::abs(angle) <= org_fov * 0.5) {
                //foodDetected = true;
                float64 dist = food.pos.distanceSq(this->pos);
                //if (dist <= minDist) {
                if (std::abs(angle) < std::abs(minAngle)){
                    minAngle = angle;
                    minDist = dist;
                    isPoison = food.poison;
                }
            }
        }
        
        
        ///*
        this->brain.setInput(this->brainInputs[1], Util::map(minAngle, -180.0, 180.0, ai_inputMapMin, ai_inputMapMax));
        this->brain.setInput(this->brainInputs[2], Util::map(Util::clamp(1.0 / std::sqrt(minDist), 0.0, 1.0), 0.0, 1.0, 0.0, ai_inputMapMax));
        this->brain.setInput(this->brainInputs[3], isPoison ? ai_inputMapMax : 0.0);
        //this->brain.setInput(this->brainInputs[4], ai_inputMapMax);
        
        minVector.x = minVector.y = -9999;
        minVectorDist = std::numeric_limits<float64>::infinity();
        
        for (int i = 0; i < cur_game->env.foods.get_size(); i++){
            if (cur_game->env.foods.isEnabled(i)){
                Food& food = cur_game->env.foods[i];
                if (food.poison) {
                    float64 dist = food.pos.distanceSq(this->pos);
                    if (dist <= minVectorDist) {
                        minVector = food.pos;
                        minVectorDist = dist;
                    }
                }
            }
        }
        
        this->brain.setInput(this->brainInputs[3], Util::map(Util::rotationDistance(this->get_rotation(), this->pos.angleTo(minVector)), -180.0, 180.0, ai_inputMapMin, ai_inputMapMax));
        this->brain.setInput(this->brainInputs[4], Util::map(Util::clamp(1.0 / this->pos.distance(minVector), 0.0, 1.0), 0.0, 1.0, 0.0, ai_inputMapMax));
        */

        
        Vec2D minVector(-9999, -9999);
        float64 minVectorDist = std::numeric_limits<float64>::infinity();
        float64 targetColor = 0.0;
        bool targetAlive = false;
        
        for (int i = 0; i < cur_game->env.population.get_size(); i++){
            if (cur_game->env.population.isEnabled(i)){
                Organism& organism = cur_game->env.population[i];
                if (organism.poolIndex != this->poolIndex){
                    float64 dist = organism.pos.distanceSq(this->pos);
                    if (dist <= minVectorDist) {
                        minVector = organism.pos;
                        minVectorDist = dist;
                        targetColor = organism.color;
                        targetAlive = organism.alive;
                    }
                }
            }
        }

        if (org_inputExtraInfo) {
            this->brain.setInput(this->brainInputs[5], Util::map(Util::rotationDistance(this->get_rotation(), this->pos.angleTo(minVector)), -180.0, 180.0, ai_inputMapMin, ai_inputMapMax));
            this->brain.setInput(this->brainInputs[6], Util::map(Util::clamp(1.0 / this->pos.distance(minVector), 0.0, 1.0), 0.0, 1.0, 0.0, ai_inputMapMax));
            this->brain.setInput(this->brainInputs[7], Util::map(targetColor, 0.0, 1.0, 0.0, ai_inputMapMax));
            this->brain.setInput(this->brainInputs[8], targetAlive ? ai_inputMapMax : 0.0);
        }
        
        //*/
        this->brain.process();
        
        float64 thrust = this->brain.getOutput(this->brainOutputs[0]) * org_maxSpeed;
        float64 turn = this->brain.getOutput(this->brainOutputs[1]) * 4.0;
        if (this->replicateCooldown <= 0 && this->brain.getOutput(this->brainOutputs[2]) > 0.5) this->replicate();
        if (org_allowFire && this->fireTimer <= 0 && this->brain.getOutput(this->brainOutputs[3]) > 0.5) this->fire(this->brain.getOutput(this->brainOutputs[4]) * 180.0);
        
        this->energy += org_energyThrustPS * std::abs(thrust);
        this->energy += org_energyTurnPS * std::abs(turn);
        
        this->rotate(turn);
        this->pos.addDirectional(thrust, this->get_rotation());
        
        if (this->pos.x < 0){
            this->pos.x = 0;
            this->vel.x = 0;
        }
        else if (this->pos.x > cur_game->get_rawWidth()){
            this->pos.x = cur_game->get_rawWidth();
            this->vel.x = 0;
        }
        if (this->pos.y < 0){
            this->pos.y = 0;
            this->vel.y = 0;
        }
        else if (this->pos.y > cur_game->get_rawHeight()){
            this->pos.y = cur_game->get_rawHeight();
            this->vel.y = 0;
        }
        
        for (int i = 0; i < cur_game->env.foods.get_size(); i++){
            if (cur_game->env.foods.isEnabled(i)){
                Food& food = cur_game->env.foods[i];
                if (food.visible && this->pos.distanceSq(food.pos) < org_foodCollisionRadius * org_foodCollisionRadius){
                    cur_game->env.removeFood(i);
                    if (food.poison){
                        this->poisonEaten++;
                        if (org_allowDeath){
                            this->alive = false;
                            cur_game->env.removeOrganism(this->poolIndex);
                            return;
                        }
                    }
                    else {
                        this->foodEaten++;
                        this->energy += org_energyFood;
                    }
                }
            }
        }
        
        for (int i = 0; i < cur_game->env.population.get_size(); i++){
            if (cur_game->env.population.isEnabled(i)){
                Organism& organism = cur_game->env.population[i];
                if (!organism.alive && this->pos.distanceSq(organism.pos) < org_corpseCollisionRadius * org_corpseCollisionRadius){
                    this->corpseEaten++;
                    this->energy += org_energyCorpse;
                    cur_game->env.removeOrganism(i);
                }
            }
        }
        
        this->energy += org_energyIdlePS;
        
        this->energy = std::min(this->energy, org_maxEnergy);
        this->energyIndicator.r = 1;
        this->energyIndicator.g = this->energyIndicator.b = this->energy / org_maxEnergy;
        this->tile.b = this->color;
        this->tile.g = 1.0;
        this->tile.r = 1.0 - this->tile.b;
        if (org_allowDeath && this->energy <= 0){
            this->alive = false;
            cur_game->env.removeOrganism(this->poolIndex);
            return;
        }
    }
    else if (this->visible){
        this->tile.r = this->tile.g = this->tile.b = 0.35;
        this->decomposeTimer--;
        if (this->decomposeTimer == 0){
            cur_game->env.removeOrganism(this->poolIndex);
        }
    }
}
