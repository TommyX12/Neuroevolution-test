#include "engine/includes/display.h"

namespace Nebula
{
    AtlasContainer::AtlasContainer()
     : AtlasElement()
    {
        
    }

    AtlasContainer::~AtlasContainer()
    {
        //dtor
    }
    
    void AtlasContainer::addChild(AtlasElement& child)
    {
        //TODO: remove last parent
        this->children.push_back(&child);
        child.parent = this;
    }
}
