#include "engine/includes/display.h"

namespace Nebula
{
    void AtlasDisplay::create(TextureAtlas& textureAtlas)
    {
        this->textureAtlas = &textureAtlas;
        this->renderStates.texture = &textureAtlas;
        sf::Vector2u textureSize = textureAtlas.getSize();
        this->textureWidth = textureSize.x;
        this->textureHeight = textureSize.y;
        
        this->motionBlur = false;
        this->updated = false;
        this->transformMode = TransformMode::GLOBAL;

        //this->mainShader.loadFromMemory(Shader::frag_test(), sf::Shader::Type::Fragment);
        //this->renderStates.shader = &this->mainShader;

        this->renderVelShader.loadFromMemory(Shader::vert_velocityBuffer(), Shader::frag_velocityBuffer());
        this->renderVelStates.shader = &this->renderVelShader;
    }
    
    AtlasDisplay::AtlasDisplay()
    : AtlasContainer()
    {
        
    }
    
    AtlasDisplay::AtlasDisplay(TextureAtlas& textureAtlas)
    : AtlasContainer()
    {
        this->create(textureAtlas);
    }
    
    

    void AtlasDisplay::update()
    {
        if (!this->paused) this->updateContainer(this);
        //this->updated = true;
    }

    void AtlasDisplay::updateContainer(AtlasContainer* container)
    {
        for (AtlasElement* child:container->children){
            if (child->paused) continue;

            child->updatePhysics();
            child->update();

            AtlasContainer* childContainer = dynamic_cast<AtlasContainer*>(child);
            AtlasElement* childC = dynamic_cast<AtlasElement*>(child);
            if (childContainer != nullptr){
                updateContainer(childContainer);
            }
        }
    }

    void AtlasDisplay::cacheLastFrame(AtlasContainer* container)
    {
        for (AtlasElement* child:container->children){
            if (!child->visible || !child->alpha) continue;

            AtlasContainer* childContainer = dynamic_cast<AtlasContainer*>(child);
            if (childContainer != nullptr){
                updateContainer(childContainer);
            }
        }
    }

    void AtlasDisplay::render(sf::RenderTarget& target, sf::RenderTexture& velocityBuffer, float velocityBufferRes, float maxMotionBlurRange, float motionBlurIntensity)
    {
        //printf("renderStart\n");
        this->vertexIndex = 0;
        this->renderContainer(this);

        //target.pushGLStates();
        target.draw(&this->vertexArray[0], this->vertexIndex, sf::Quads, this->renderStates);
        //target.popGLStates();

        velocityBuffer.clear(sf::Color(127, 127, 0, 0));
        
        if (motionBlur){
            sf::Vector2u bufferSize = velocityBuffer.getSize();
            this->renderVelShader.setParameter("resolution", bufferSize.x, bufferSize.y);
            this->renderVelShader.setParameter("scale", velocityBufferRes);
            this->renderVelShader.setParameter("scaleOffset", 1.0 - velocityBufferRes, velocityBufferRes - 1.0);
            this->renderVelShader.setParameter("velMul", 1.0 / (velocityBufferRes * maxMotionBlurRange) * motionBlurIntensity);
            this->renderVelShader.setParameter("current", sf::Shader::CurrentTexture);
            this->renderVelStates.texture = this->renderStates.texture;
            //velocityBuffer.pushGLStates();
            velocityBuffer.draw(&this->vertexVelArray[0], this->vertexIndex, sf::Quads, this->renderVelStates);
            //velocityBuffer.popGLStates();
        }
        
        

        //this->updated = false;
        //printf("renderEnd\n");
    }

    void AtlasDisplay::renderContainer(AtlasContainer* container)
    {
        
        container->update_globalTransform();
        for (AtlasElement* child:container->children){
                
            

            if (child->visible == false || child->alpha == 0.0) continue;

            AtlasContainer* childContainer = dynamic_cast<AtlasContainer*>(child);
            if (childContainer != nullptr){
                this->renderContainer(childContainer);
                continue;
            }
            
            
            AtlasEntity* childEntity = dynamic_cast<AtlasEntity*>(child);
            if (childEntity != nullptr && childEntity->textureAtlas == this->textureAtlas){
                Transform & transform = childEntity->update_globalTransform();
                if (this->vertexIndex >= this->vertexArray.size()){
                    this->vertexArray.push_back(sf::Vertex());
                    this->vertexArray.push_back(sf::Vertex());
                    this->vertexArray.push_back(sf::Vertex());
                    this->vertexArray.push_back(sf::Vertex());
                    this->vertexVelArray.push_back(sf::Vertex());
                    this->vertexVelArray.push_back(sf::Vertex());
                    this->vertexVelArray.push_back(sf::Vertex());
                    this->vertexVelArray.push_back(sf::Vertex());
                }
                for (int i = 0; i < 4; i++){
                    sf::Vertex& vertex = this->vertexArray[this->vertexIndex + i];
                    Vec2D& modelPos = childEntity->vertModelPos[i];
                    modelPos += childEntity->offset;
                    vertex.position.x = modelPos.x * transform.a + modelPos.y * transform.b + transform.tx;
                    vertex.position.y = modelPos.x * transform.c + modelPos.y * transform.d + transform.ty;
                    vertex.texCoords.x = childEntity->vertTexCoord[i].x;
                    vertex.texCoords.y = childEntity->vertTexCoord[i].y;
                    vertex.color.r = transform.red * 255;
                    vertex.color.g = transform.green * 255;
                    vertex.color.b = transform.blue * 255;
                    vertex.color.a = transform.alpha * 255;

                    if (motionBlur){
                        sf::Vertex& vertexVel = this->vertexVelArray[this->vertexIndex + i];
                        //TODO
                        vertexVel.position = vertex.position;
                        if (!childEntity->syncedMotionBlur){
                            vertexVel.texCoords.x = vertex.position.x;
                            vertexVel.texCoords.y = vertex.position.y;
                        }
                        else {
                            vertexVel.texCoords.x = childEntity->vertLastPos[i].x;
                            vertexVel.texCoords.y = childEntity->vertLastPos[i].y;
                        }
                        //printf("%llf\n", vertexVel.position.x - vertexVel.texCoords.x);
                        uint texCoordX = vertex.texCoords.x * 65536 / this->textureWidth;
                        uint texCoordY = vertex.texCoords.y * 65536 / this->textureHeight;
                        vertexVel.color.r = texCoordX >> 8;
                        vertexVel.color.g = texCoordX & 0xff;
                        vertexVel.color.b = texCoordY >> 8;
                        vertexVel.color.a = texCoordY & 0xff;

                        //if (!i) printf("%d %d %lf %lf\n", vertexVel.color.r, vertexVel.color.g, (float64)texCoordX / 65536.0, vertex.texCoords.x / this->textureWidth);
                        //if (!this->updated){
                        //}
                    }
                    childEntity->vertLastPos[i].x = vertex.position.x;
                    childEntity->vertLastPos[i].y = vertex.position.y;
                }
                childEntity->syncedMotionBlur = true;
                this->vertexIndex += 4;
            }
        }
    }
}
