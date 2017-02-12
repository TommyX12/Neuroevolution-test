#pragma once
/*

    //TODO: find a way upload tex coord and tex alpha for vel buffer.
        //TODO: try to pass pseudo depth to vel extend shader
        //WARNING: if vector stores value, pointer to value in vector, it is NOT safe.
        //TODO: premultiplied alpha
        
        //AI:
            able to export a trainned network
            try back to use artificial selection instead of dynamic simulation environment
            try custom neurons, ex memory units
            make cellular-like game, make organism evolve best configuration of cells
            visualize the network
            MAYBE NOT: remember to adjust so that input neurons have value between [-1, 1]
            maybe evolve an "identifier" / color data that nearby creature can use as input
            try to evolve mutation rate, weightMinMax and other GA params as well.
            try diff func on neurons.
            verify that things are working correctly
            play with ALL global params.
            try diff types of NN, feedforward, recursive, grid, etc.
            maybe mutation will only increase/decrease instead of reset.
            change crossover method
            change mutation rate
            change reproduction method: sexual, asexual, only reproduce when touch, 
            acquire food from dead body
            random elements to play with (train to use tool)
            change input methods (communication, local vision, friends, get food from deadbody, rasterization of fov w/ visual cortex, a constant 1.0 input, since all input 0.0 will give no output)
            try change trainning methods, such as back prop
            try make input being closest food in terms of least angle from facing, with a tag of isPoison
            
            

    store tutorials locally

    setup:
        make sure compiler version matches.
        copy dll from compiler and SFML
        link opengl
        get glew(follow open.gl), when linking, move to top of linker list
        use resourcePath() + ... to load stuff

    game loop idea:
        sf::Clock clock;
        sf::Time accumulator = sf::Time::Zero;
        sf::Time ups = sf::seconds(1.f / 60.f);

        while (windows.isOpen())
        {
            ProcessEvents();

            while (accumulator > ups)
            {
                accumulator -= ups;
                UpdateLogic();
                //AI();
                //Physics();
            }

            Render();
            accumulator += clock.restart();
        }


	later: learn multi-threading for drawing or loading.

	@ port part of openfl nebula library:

        Mac:
            no GLEW
            glVertexArray use APPLE suffix
            when importing folder, use create group so compile sources will be added auto
            add $SOURCE_ROOT to user headers
			use resourcePath without folder to get image

        TileSheet becomes VertexArray. use color for transparency. Or maybe use raw OpenGL draw
            http://hacksoflife.blogspot.ca/2010/02/double-buffering-vbos.html
            http://stackoverflow.com/questions/4854565/opengl-vbo-updating-data
            http://www.gamedev.net/topic/658256-using-vbos-for-dynamic-geometry/
        use sfml Texture, Shader and VertexArray
        write my OpenGL abstraction layer.
        Stage Scale Mode
        Objects have manual constructor func called create, which is user called
        take good care of OpenGL states that are changed by SFML
        GLSL: vert out and frag in must have same name
        use vertex z coord for depth, then use vertex shader for transformation, parallax, motion blur, view frustrum culling
        if using custom opengl renderer, can make some geometry static so vbo don't get updated
        either add z coord attribute (also last frame pos) to sfml, or use software for parallax(calculate obj matrix, apply with software) and motion blur velocity buffer
        if possible, use geometry shader to generate 4 vert from 1 point
        motionblur:
            use second pass to draw to velocity buffer. This time use color R and G to represent last frame position.
            http://john-chapman-graphics.blogspot.ca/2013/01/per-object-motion-blur.html
        GPU particle system: use texture.
        frag shader write to multiple buffer
        VAO is only for above 3.0
        Use custom function bindings for different versions, ex. framebuffer EXT or ARB(no suffix)

        CPU cache once > GPU for each > CPU for each

        Keep in mind to Make into an modular framework, which can adapt to any backend:
            no access to OS specific functions inside framework
            framework should be abstract, and interface should only be used to access the framework instead of being part of it
            use conditional compilation
            use generalized abstraction layer methods, ex. call a func and then that function redirect to specific ones. Same goes for type and var.

        for Qt integration:
            http://becomingindiedev.blogspot.ca/2013/10/qt-5-and-sfml-20-integration.html

    Also add functionality to do very little rendering, like CPU GUI which only update part of it.

    Safe check to wait after drawing if forced no vSync

	try timeElapsed based movement combined with current game loop. Limit max queue so when window paused, no huge update after coming back on.
	if good, port to Cellular.
        sf::Time updateTime;
        sf::Clock updateClock

        while (window.isOpen()) {
            // Event handling is performed here

            // Determine the time that passed
            sf::Time delta = updateClock.restart();

            updateTime += delta; // add up previous leftover time

            int loops = std::min<int>((int)(updateTime / sf::milliseconds(10)), 10); // determine the number of iterations to do (100 fps; capped at 10)
            while (loops--)
                updateSingleStep(); // update by one fixed timestep

            updateTime %= sf::milliseconds(10); // drop leftover frames

            updateDeltaTime(delta); // update based on time passed

            window.clear();
            // rendering
            window.display();

            sf::Sleep(sf::microsecond(1)); // sleep a minimum amount of time to ensure there's always at least some delta time (assuming very, very fast CPUs).
        }




*/

namespace Nebula
{
    class NebulaGame
    {
        public:

            bool lockMouse;

            sf::RenderWindow window;
            //sf::RenderWindow *p_window;
            sf::Time timeElapsed;
            
            sf::Font defaultFont;
            
            bool pauseOnFocusLoss;

            NebulaGame(int, int, std::string, int);
            virtual ~NebulaGame();

            int execute();
            
            void addLayer(AtlasDisplay&);
            void addText(sf::Text&);

            //getter / setters:
            float64 get_time();
            int get_rawWidth();
            int get_rawHeight();
            int get_width();
            int get_height();
            int get_fps();
            bool get_hasFocus();

            int set_fps(int);
            
            float velocityBufferRes, motionBlurMaxRange, motionBlurSampleCount, motionBlurIntensity;
            

        protected:
        private:
            std::vector<AtlasDisplay*> layers;
            std::vector<sf::Text*> texts;
            int rawWidth, rawHeight, width, height, fps;
            bool hasFocus;
            sf::Clock clock;
            sf::Time updateDelay;
            float64 updateDelaySecond, time;
    };
}
