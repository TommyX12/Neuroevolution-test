#pragma once

namespace Nebula
{
    class AtlasContainer;

    class AtlasElement
    {
        public:

            AtlasContainer *parent;

            int transformMode;

            Vec2D pos;
            float64 depth;
            Vec2D vel;
        

            bool visible, paused;

            AtlasElement();
            virtual ~AtlasElement();
        
            virtual void updatePhysics();
            virtual void update();
            
            float64 r;
            float64 g;
            float64 b;
            float64 alpha;

            //getter / setter
            float64 get_rotation();
            float64 get_scaleX();
            float64 get_scaleY();
        /*
            float64 get_skewX();
            float64 get_skewY();
         */
            float64 get_width();
            float64 get_height();
            Transform& get_localTransform();
            Transform& update_globalTransform();
            Transform globalTransform;

            float64 set_rotation(float64);
            float64 set_scale(float64);
            float64 set_scaleX(float64);
            float64 set_scaleY(float64);
            float64 rotate(float64);
        /*
            float64 set_skewX(float64);
            float64 set_skewY(float64);
            float64 set_width(float64);
            float64 set_height(float64);
        */
        protected:

        private:
            bool dirty;
            float64 rotation, rotationOld, rotationCos, rotationSin, width, height;
            float64 scaleX, scaleY, skewX, skewY;
            Transform localTransform;
        
    };
}

