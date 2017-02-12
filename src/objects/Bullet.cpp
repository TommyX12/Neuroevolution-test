#include "includes/objects.h"
#include "includes/gameGlobal.h"

using namespace Nebula;

Bullet::Bullet()
{
    //ctor
}

void Bullet::create()
{
    this->tile.create(cur_game->shapesAtlas, "square");
    
    this->tile.set_scaleY(0.07);
    this->tile.set_scaleX(0.2);
    this->addChild(this->tile);
    
    this->tile.r = 1.0;
    this->tile.g = 1.0;
    this->tile.b = 0.8;
}

void Bullet::reset(Vec2D& pos, float64 rotation)
{
    this->set_rotation(rotation);
    this->pos = pos;
    this->vel.reset().addDirectional(b_startingVel, rotation);
}

void Bullet::update()
{
    this->vel *= b_friction;
    
    if (this->vel.lengthSq() < 0.01) {
        cur_game->env.removeBullet(this->poolIndex);
        return;
    }
    
    if (!Rectangle(0, 0, cur_game->get_rawWidth(), cur_game->get_rawHeight()).contains(this->pos, b_screenBoundMargin)){
        cur_game->env.removeBullet(this->poolIndex);
        return;
    }
    
    for (int i = 0; i < cur_game->env.population.get_size(); i++){
        if (cur_game->env.population.isEnabled(i)){
            Organism& organism = cur_game->env.population[i];
            if (organism.visible && organism.alive && this->pos.distanceSq(organism.pos) < org_bulletCollisionRadius * org_bulletCollisionRadius){
                
                //organism.energy += org_energyBulletDamage;
                
                organism.alive = false;
                
                cur_game->env.removeBullet(this->poolIndex);
                return;
            }
        }
    }
}



Bullet::~Bullet()
{
    //dtor
}
