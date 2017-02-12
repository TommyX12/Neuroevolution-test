#include "engine/includes/all.h"

//#include "ResourcePath.hpp"


namespace Nebula
{
    NebulaGame::NebulaGame(int width, int height, std::string title, int fps)
    {
        this->time = 0.0;

        this->rawWidth = width;
        this->rawHeight = height;
        this->width = width;
        this->height = height;
        this->set_fps(fps);

        sf::ContextSettings settings;
        settings.antialiasingLevel = 4;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        
        this->velocityBufferRes = 0.5;
        this->motionBlurMaxRange = 32.0;
        this->motionBlurSampleCount = 12;
        this->motionBlurIntensity = 0.35;

        this->window.create(sf::VideoMode(this->rawWidth, this->rawHeight), title, sf::Style::Default, settings);
        //this->window.setFramerateLimit(fps);
        this->window.setVerticalSyncEnabled(true);

        /*
        this->lockMouse = true;
        this->window.setMouseCursorVisible(false);
         */

        this->hasFocus = true;
        //this->p_window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->title, sf::Style::Default);
    }

    NebulaGame::~NebulaGame()
    {
        //delete this->p_window;
    }



    int NebulaGame::execute()
    {

        GL::init();

        //float64 time = 0;

        /*
        //x, y, z, texX, texY, r, g, b, a
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f
        };

        //use draw array to draw according to order in vertices array
        //if we want to reuse vertex, then we can define special order for vertices to be drawn, so they can be reused.
        int elements[] = {
            0, 1, 2,
            2, 3, 0
        };

        GL::setBlendMode();

        //buffer objects are just data storage on GPU (compared to CPU)

        GL::VertexArrayObject vao = GL::createVertexArrayObject(); //container of how to interpret vertex data in terms of attributes passed to shader. 3.0 above
        GL::setActiveVertexArrayObject(vao);

        GL::VertexBufferObject vbo = GL::createVertexBufferObject(); //container of vertex data
        GL::setActiveVertexBufferObject(vbo);
        GL::uploadVertexBufferData(vertices, sizeof(vertices), GL::BufferUploadType::STREAM_DRAW); //upload vertices to GL_ARRAY_BUFFER

        GL::ElementBufferObject ebo = GL::createElementBufferObject(); //container of how the vertex are arranged (can reuse vertex)
        GL::setActiveElementBufferObject(ebo);
        GL::uploadElementBufferData(elements, sizeof(elements), GL::BufferUploadType::DYNAMIC_DRAW);

        GL::VertexShader vertexShader = GL::createVertexShader();
        GL::uploadShaderSource(vertexShader, Shader::vert_default());

        GL::FragmentShader fragmentShader = GL::createFragmentShader();
        GL::uploadShaderSource(fragmentShader, Shader::frag_default());

        GL::ShaderProgram shaderProgram = GL::createShaderProgram(vertexShader, fragmentShader); //combined shader of vert and frag

        GL::setActiveShaderProgram(shaderProgram);

        GL::VertexAttribute attribPosition = GL::createVertexAttribute(shaderProgram, "positionIn");
        GL::defineVertexAttribute(attribPosition, 0, 9, 3, 0, sizeof(float), GL::DataType::FLOAT, false);
        GL::enableVertexAttribute(attribPosition); //enable it

        GL::VertexAttribute attribColor = GL::createVertexAttribute(shaderProgram, "colorIn");
        GL::defineVertexAttribute(attribColor, 0, 9, 4, 3, sizeof(float), GL::DataType::FLOAT, false);
        GL::enableVertexAttribute(attribColor);

        GL::VertexAttribute attribTexCoord = GL::createVertexAttribute(shaderProgram, "texCoordIn");
        GL::defineVertexAttribute(attribTexCoord, 0, 9, 2, 7, sizeof(float), GL::DataType::FLOAT, false);
        GL::enableVertexAttribute(attribTexCoord);

        GL::ShaderParam paramTime = GL::createShaderParam(shaderProgram, "time");
        GL::ShaderParam paramMatModel = GL::createShaderParam(shaderProgram, "matModel");
        GL::ShaderParam paramMatView = GL::createShaderParam(shaderProgram, "matView");
        GL::ShaderParam paramMatProjection = GL::createShaderParam(shaderProgram, "matProjection");
        GL::ShaderParam paramTexBattleship = GL::createShaderParam(shaderProgram, "texture_battleship");
        GL::ShaderParam paramTexOpenGL = GL::createShaderParam(shaderProgram, "texture_opengl");


        AtlasElement tile;

        sf::Uint8* pixels = new sf::Uint8[width * height * 4];

        glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
        float cameraYaw = -90.0;
        float cameraPitch = 0.0;
        //float cameraRoll = 0.0;
        glm::vec3 cameraAngle = glm::vec3(0.0, 0.0, -1.0);
        glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);

        glm::vec3 cameraVel = glm::vec3(0.0, 0.0, 0.0);

        float cameraForce = 0.01;
        float cameraFriction = 0.7;
        float cameraTurnSpeed = 0.05;
        */

        /*
        TextureAtlas texture_battleship;
        //texture_battleship.update(pixels);
        //if (!texture_battleship.loadFromFile(resourcePath() + "battleship.jpg")) return -1;
        if (!texture_battleship.loadFromFile("textures/battleship.jpg")) return -1;
        texture_battleship.setSmooth(true);
        
        texture_battleship.addTileData("test1", Rectangle(0,0,100,100));
        texture_battleship.addTileData("test2", Rectangle(0,0,1280,531));

        TextureAtlas texture_opengl;
        //texture_opengl.update(pixels);
        //if (!texture_opengl.loadFromFile(resourcePath() + "opengl.png")) return -1;
        if (!texture_opengl.loadFromFile("textures/opengl.png")) return -1;
        texture_opengl.setSmooth(true);

        texture_opengl.addTileData("test1", Rectangle(0,0,100,100));
        texture_opengl.addTileData("test2", Rectangle(0,0,1280,531));
        
        */

        sf::RenderTexture screenBuffer;
        screenBuffer.create(this->width, this->height);
        screenBuffer.setSmooth(true);
        sf::Sprite screenSprite(screenBuffer.getTexture());

        sf::RenderTexture velocityBuffer;
        velocityBuffer.create(this->width * this->velocityBufferRes, this->height * this->velocityBufferRes);
        velocityBuffer.setSmooth(false);
        sf::Sprite velocitySprite(velocityBuffer.getTexture());
        //screenSprite.setScale(1.0 / velocityBufferRes, 1.0 / velocityBufferRes);

        sf::CircleShape shape(30);
        shape.setFillColor(sf::Color::Red);

        /*
        AtlasDisplay layer(texture_battleship);
        layer.motionBlur = true;
        AtlasContainer container;
        AtlasEntity tile(texture_battleship, "test2"), tile2(texture_battleship, "test1");
        container.addChild(tile);
        //container.addChild(tile2);
        //tile.offset = Vec2D(-25, -25);
        //tile.pos = Vec2D(200, 0);
        //tile.set_scaleY(0.5);
        //tile.set_rotation(50);
        //container.set_scaleX(0.5);
        //tile.transformMode = TransformMode::GLOBAL;
        layer.addChild(container);
        */
        defaultFont.loadFromFile("fonts/font.otf");

        sf::Shader motionBlurShader;
        motionBlurShader.loadFromMemory(Shader::frag_motionBlur(this->motionBlurSampleCount), sf::Shader::Type::Fragment);

        sf::Shader velocityExpandShader;
        velocityExpandShader.loadFromMemory(Shader::frag_velocityExpand(), sf::Shader::Type::Fragment);

        sf::RenderStates renderStates;
        
        sf::Time reseedTime = sf::seconds(1);
        sf::Time reseedTimeElapsed;

        bool drawn = false;
        bool running = true;
        while (running)
        {
            sf::Event event;
            while (this->window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) running = false;
                else if (event.type == sf::Event::Resized) {
                    this->width = event.size.width;
                    this->height = event.size.height;
                    //screenBuffer.create(this->width, this->height);
                    //screenSprite.setTexture(screenBuffer.getTexture());
                }
                else if (event.type == sf::Event::LostFocus){
                    this->hasFocus = false;
                    if (this->pauseOnFocusLoss) this->window.setFramerateLimit(10);
                }
                else if (event.type == sf::Event::GainedFocus){
                    this->hasFocus = true;
                    this->window.setFramerateLimit(0);
                }
            }

            int loops = std::min<int>((int)(this->timeElapsed / this->updateDelay), 10); // determine the number of iterations to do (capped at 10)
            //if (loops >= 2) printf("what the FUCK!\n");
            while (loops--)
            {
                drawn = false;
                if (this->hasFocus || !this->pauseOnFocusLoss){
                    //update logic;

                    /*
                    sf::Vector2i mouseDelta = sf::Mouse::getPosition(this->window) - sf::Vector2i(this->width / 2, this->height / 2);

                    cameraYaw = std::fmod(cameraYaw + cameraTurnSpeed * mouseDelta.x, 360.0f);
                    cameraPitch = cameraPitch - cameraTurnSpeed * mouseDelta.y;
                    if (cameraPitch > 89.9) cameraPitch = 89.9;
                    if (cameraPitch < -89.9) cameraPitch = -89.9;

                    cameraAngle.x = cos(glm::radians(cameraYaw));
                    cameraAngle.z = sin(glm::radians(cameraYaw));
                    cameraAngle.y = tan(glm::radians(cameraPitch));

                    cameraAngle = glm::normalize(cameraAngle);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                        cameraVel += cameraAngle * cameraForce;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                        cameraVel -= cameraAngle * cameraForce;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                        cameraVel -= glm::normalize(glm::cross(cameraAngle, cameraUp)) * cameraForce;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                        cameraVel += glm::normalize(glm::cross(cameraAngle, cameraUp)) * cameraForce;
                    }

                    cameraPos += cameraVel;
                    cameraVel *= cameraFriction;

                    shape.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                    tile.set_rotation(tile.get_rotation() + 1.0);
                    if (tile.get_rotation() > 360.0) tile.set_rotation(tile.get_rotation() - 360.0);
                    if (tile.get_rotation() < 0.0) tile.set_rotation(tile.get_rotation() + 360.0);
                     */

                    ///*
                    
                    if ((int)(reseedTimeElapsed / reseedTime)){
                        //Util::_gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
                        reseedTimeElapsed %= reseedTime;
                    }
                    
                    sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
                    
                    Input::mousePos.x = mousePos.x;
                    Input::mousePos.y = mousePos.y;
                    //*/

                    /*
                    container.pos.x = mousePos.x;
                    container.pos.y = mousePos.y;

                    container.set_scaleX(sin(time * 3.0));
                    container.set_scaleY(sin(time * 3.0));
                    //container.set_rotation((container.get_rotation() + 3));
                    if (container.get_rotation() > 360) container.set_rotation(container.get_rotation() - 360.0);
                    */
                    
                    

                    for (AtlasDisplay* layer:this->layers){
                        layer->update();
                    }

                    time += this->updateDelaySecond;
                    

                    if (this->lockMouse){
                        sf::Mouse::setPosition(sf::Vector2i(this->width / 2, this->height / 2), this->window);
                    }
                }
            }

            this->timeElapsed %= this->updateDelay;
            //optional update by delta

            if (this->hasFocus || !this->pauseOnFocusLoss){

                this->window.clear(sf::Color::Transparent);

                if (!drawn){
                    drawn = true;

                    //this->window.clear();
                    screenBuffer.clear(sf::Color::Transparent);
                    velocityBuffer.clear(sf::Color::Transparent);

                    /*

                    //gl draws
                    //this->window.setActive();
                    //screenBuffer.setActive();

                    GL::setViewport(0, 0, this->get_width(), this->get_height());

                    GL::enableDepthTest();

                    GL::clearColorBuffer(0.0, 0.0, 0.0, 0.0);
                    GL::clearDepthBuffer(1.0);

                    GL::setActiveVertexArrayObject(vao);
                    GL::setActiveVertexBufferObject(vbo);
                    GL::setActiveElementBufferObject(ebo);
                    GL::setActiveShaderProgram(shaderProgram);

                    GL::setActiveTexture(0, texture_battleship.getNativeHandle());
                    GL::setActiveTexture(1, texture_opengl.getNativeHandle());

                    //transformation:
                    //order should be reversed since B transform is applied first then A

                    glm::mat4 matModel, matView, matProjection;
                    matModel = glm::translate(matModel, glm::vec3(tile.pos.x, tile.pos.y, 0.0));
                    matModel = glm::rotate(matModel, (float)glm::radians(tile.get_rotation()), glm::vec3(0.5, 0.0, 1.0));
                    matModel = glm::scale(matModel, glm::vec3(tile.get_scaleX(), tile.get_scaleX(), tile.get_scaleX()));

                    matView = glm::lookAt(cameraPos, cameraPos + cameraAngle, cameraUp);

                    matProjection = glm::perspective(glm::radians(70.0), (float64)this->get_width() / this->get_height(), 0.1, 100.0);

                    GL::uploadShaderParam(paramTime, (float)time);
                    GL::uploadShaderParam(paramTexBattleship, 0);
                    GL::uploadShaderParam(paramTexOpenGL, 1);
                    GL::uploadShaderParam(paramMatModel, matModel);
                    GL::uploadShaderParam(paramMatView, matView);
                    GL::uploadShaderParam(paramMatProjection, matProjection);
                    //glDrawArrays(GL_TRIANGLES, 0, 6); //type of primitive, starting vert, number of verts
                    GL::renderVertices(GL::RenderMode::TRIANGLES, 0, 36); //type of primitive, starting vert, number of verts
                    //glDrawArrays(GL_QUADS, 0, 4); //type of primitive, starting vert, number of verts
                    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //type of primitive, number of verts, element index type, starting vert

                    GL::clearAllActive();
                    GL::disableDepthTest();

                    //sfml drawing
                     */

                    //render
                    for (AtlasDisplay* layer:this->layers){
                        layer->render(screenBuffer, velocityBuffer, this->velocityBufferRes, this->motionBlurMaxRange, this->motionBlurIntensity);
                    }

                    velocityBuffer.display();
                    screenBuffer.display();
                    
                    renderStates.blendMode = sf::BlendNone;
                    sf::Vector2u texSize = velocityBuffer.getSize();
                    renderStates.shader = &velocityExpandShader;
                    velocityExpandShader.setParameter("resolution", texSize.x, texSize.y);
                    velocityExpandShader.setParameter("current", sf::Shader::CurrentTexture);
                    velocityBuffer.draw(velocitySprite, renderStates);
                    velocityBuffer.display();
                }

                this->window.setActive();
                //GL::clearAllActive();

                //this->window.pushGLStates();
                sf::Vector2u texSize = screenBuffer.getSize();
                renderStates.blendMode = sf::BlendNone;
                renderStates.shader = &motionBlurShader;
                motionBlurShader.setParameter("resolution", texSize.x, texSize.y);
                motionBlurShader.setParameter("current", sf::Shader::CurrentTexture);
                motionBlurShader.setParameter("velocity", velocityBuffer.getTexture());
                motionBlurShader.setParameter("stepMul", this->motionBlurMaxRange / (float)this->motionBlurSampleCount);
                this->window.draw(screenSprite, renderStates);
                for (sf::Text* text:this->texts){
                    this->window.draw(*text);
                }
                //this->window.popGLStates();
            }

            this->window.display();

            sf::Time timeDelta = this->clock.restart();
            this->timeElapsed += timeDelta;
            reseedTimeElapsed += timeDelta;
        }

        //clean up
        /*
        GL::deleteVertexArrayObject(&vao);

        GL::deleteVertexBufferObject(&vbo);
        GL::deleteElementBufferObject(&ebo);

        GL::deleteShader(fragmentShader);
        GL::deleteShader(vertexShader);
        GL::deleteShaderProgram(shaderProgram);
         */

        this->window.close();

        return 0;

    }
    
    void NebulaGame::addLayer(AtlasDisplay& layer)
    {
        this->layers.push_back(&layer);
    }
    
    void NebulaGame::addText(sf::Text& text)
    {
        this->texts.push_back(&text);
    }

    //getter / setters
    
    float64 NebulaGame::get_time()
    {
        return this->time;
    }
    
    int NebulaGame::get_rawWidth()
    {
        return this->rawWidth;
    }

    int NebulaGame::get_rawHeight()
    {
        return this->rawHeight;
    }

    int NebulaGame::get_width()
    {
        return this->width;
    }

    int NebulaGame::get_height()
    {
        return this->height;
    }

    int NebulaGame::get_fps()
    {
        return this->fps;
    }
    
    bool NebulaGame::get_hasFocus()
    {
        return this->hasFocus;
    }

    int NebulaGame::set_fps(int fps)
    {
        this->fps = fps;
        this->updateDelaySecond = (float64)1.0 / (float64)fps;
        this->updateDelay = sf::seconds(this->updateDelaySecond);
        return this->fps;
    }
}
/** \brief 
 *
 * \param 
 * \param 
 * \return 
 *
 */     
