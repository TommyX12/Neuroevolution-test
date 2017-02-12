#include "engine/includes/display.h"

namespace Nebula
{
    TextureAtlas::TextureAtlas()
    : sf::Texture()
    {
        
    }
    
    Rectangle& TextureAtlas::getTileData(std::string name)
    {
        return this->tileData[this->tileIndexMap[name]];
    }
    
    void TextureAtlas::addTileData(std::string name, Rectangle data)
    {
        this->tileIndexMap[name] = this->tileData.size();
        this->tileData.push_back(data);
        
    }
}
