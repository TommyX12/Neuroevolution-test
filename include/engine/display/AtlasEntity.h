#pragma once

namespace Nebula
{
    
    class AtlasEntity: public AtlasElement
    {
    public:
        //AtlasEntity();
        AtlasEntity();
        AtlasEntity(TextureAtlas&, std::string);
        void create(TextureAtlas&, std::string);
        TextureAtlas* textureAtlas;
        virtual ~AtlasEntity();
        Vec2D vertModelPos[4];
        Vec2D vertTexCoord[4];
        Vec2D vertLastPos[4];
        Vec2D offset;
        
        bool syncedMotionBlur;
        
        std::string get_tile();
        
        std::string set_tile(std::string);
        
    private:
        float64 texWidth, texHeight;
        std::string tile;
        
    };
    
}

