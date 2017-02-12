#pragma once

namespace Nebula
{

    class AtlasDisplay: public AtlasContainer
    {
    public:
        AtlasDisplay();
        void create(TextureAtlas&);
        AtlasDisplay(TextureAtlas&);
        void render(sf::RenderTarget&, sf::RenderTexture&, float, float, float);
        void update();
        bool motionBlur;
    private:
        bool updated;
        TextureAtlas* textureAtlas;
        int vertexIndex; // next available i in vertexArray
        std::vector<sf::Vertex> vertexArray, vertexVelArray;
        void renderContainer(AtlasContainer*);
        void updateContainer(AtlasContainer*);
        void cacheLastFrame(AtlasContainer*);
        sf::RenderStates renderStates, renderVelStates;
        sf::Shader mainShader, renderVelShader;
        int textureWidth, textureHeight;
        //sf::Texture* texture;
    };

}

