#include "includes/objects.h"
#include "includes/gameGlobal.h"

using namespace Nebula;

Food::Food()
{
    //ctor
}

void Food::create()
{
    this->tile.create(cur_game->shapesAtlas, "circle");
    this->addChild(this->tile);
    this->tile.set_scale(g_foodScale);
    this->poison = false;
}

void Food::update()
{
    if (this->poison){
        this->tile.r = 1.0;
        this->tile.g = 0.1;
        this->tile.b = 0.1;
    }
    else {
        this->tile.r = 0.1;
        this->tile.g = 1.0;
        this->tile.b = 0.1;
    }
}

Food::~Food()
{
    //dtor
}
