#pragma once

namespace Nebula
{
    
    class TextureAtlas: public sf::Texture
    {
    public:
        TextureAtlas();
        Rectangle& getTileData(std::string);
        void addTileData(std::string, Rectangle);
    private:
        std::map<std::string, int> tileIndexMap;
        std::vector<Rectangle> tileData;
        
    };
    
}

