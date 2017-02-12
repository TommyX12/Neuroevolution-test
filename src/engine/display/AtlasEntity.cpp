#include "engine/includes/display.h"

namespace Nebula
{
    
    void AtlasEntity::create(TextureAtlas& textureAtlas, std::string tile)
    {
        this->textureAtlas = &textureAtlas;
        this->set_tile(tile);
        
        this->syncedMotionBlur = false;
    }
    
    AtlasEntity::AtlasEntity()
    {
        
    }
    
    AtlasEntity::AtlasEntity(TextureAtlas& textureAtlas, std::string tile)
    {
        this->create(textureAtlas, tile);
    }
    
    /*
    AtlasEntity::AtlasEntity()
    {
        this->textureAtlas = nullptr;
    }
    */
    AtlasEntity::~AtlasEntity()
    {
        
    }
    
    std::string AtlasEntity::get_tile()
    {
        return this->tile;
    }
    
    std::string AtlasEntity::set_tile(std::string tile)
    {
        this->tile = tile;
        
        Rectangle& rect = this->textureAtlas->getTileData(tile);
        
        this->texWidth = rect.width;
        this->texHeight = rect.height;
        
        this->vertModelPos[0].x = -this->texWidth/2;
        this->vertModelPos[0].y = -this->texHeight/2;
        this->vertModelPos[1].x = this->texWidth/2;
        this->vertModelPos[1].y = -this->texHeight/2;
        this->vertModelPos[2].x = this->texWidth/2;
        this->vertModelPos[2].y = this->texHeight/2;
        this->vertModelPos[3].x = -this->texWidth/2;
        this->vertModelPos[3].y = this->texHeight/2;
        
        this->vertTexCoord[0].x = rect.left; this->vertTexCoord[0].y = rect.top;
        this->vertTexCoord[1].x = rect.left + this->texWidth - 1; this->vertTexCoord[1].y = rect.top;
        this->vertTexCoord[2].x = rect.left + this->texWidth - 1; this->vertTexCoord[2].y = rect.top + this->texHeight - 1;
        this->vertTexCoord[3].x = rect.left; this->vertTexCoord[3].y = rect.top + this->texHeight - 1;
        
        return this->tile;
    }
    
}
