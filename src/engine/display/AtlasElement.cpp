#include "engine/includes/display.h"

namespace Nebula
{
    AtlasElement::AtlasElement()
    {
        this->parent = nullptr;
        this->transformMode = TransformMode::LOCAL;
        this->depth = this->rotation = this->rotationOld = this->rotationSin = this->rotationCos = this->skewX = this->skewY = 0;
        this->visible = true;
        this->paused = false;
        this->dirty = true;
        this->scaleX = this->scaleY = 1;
        this->width = this->height = 0;
        this->alpha = this->r = this->g = this->b = 1.0;
    }

    AtlasElement::~AtlasElement()
    {
        //dtor
    }

    void AtlasElement::updatePhysics()
    {
        this->pos += this->vel;
    }
    
    void AtlasElement::update()
    {
        
    }

    //getter / setter
    float64 AtlasElement::get_rotation()
    {
        return this->rotation;
    }

    float64 AtlasElement::get_scaleX()
    {
        return this->scaleX;
    }

    float64 AtlasElement::get_scaleY()
    {
        return this->scaleY;
    }
    /*

    float64 AtlasElement::get_skewX()
    {
        return this->skewX;
    }

    float64 AtlasElement::get_skewY()
    {
        return this->skewY;
    }
    */
    float64 AtlasElement::get_width()
    {
        return this->width;
    }
    
    float64 AtlasElement::get_height()
    {
        return this->height;
    }

    Transform& AtlasElement::get_localTransform()
    {
        if (this->dirty)
		{
			this->dirty = false;
			float64 sx = this->scaleX;// * layer.texture.scale;
			float64 sy = this->scaleY;// * layer.texture.scale;
			if (this->rotation != 0) {
				if (this->rotation != this->rotationOld) {
					this->rotationOld = this->rotation;
					float64 radians = Convert::rad(rotation);
					this->rotationSin = std::sin(radians);
					this->rotationCos = std::cos(radians);
				}
                /*
				if (this->skewX != 0 || this->skewY != 0) {
					float64 skx = this->skewX;// * layer.texture.scale;
					float64 sky = this->skewY;// * layer.texture.scale;
					localTransform.a = sx * (this->rotationCos - this->rotationSin * sky);
					localTransform.b = sx * (this->rotationSin + this->rotationCos * sky);
					localTransform.c = sy * (this->rotationCos * skx - this->rotationSin);
					localTransform.d = sy * (this->rotationCos + this->rotationSin * skx);
				}
                 */
					this->localTransform.a = this->rotationCos * sx;
					this->localTransform.b = -this->rotationSin * sy;
					this->localTransform.c = this->rotationSin * sx;
					this->localTransform.d = this->rotationCos * sy;
			}
			else {
                /*
				if (this->skewX != 0 || this->skewY != 0) {
					float64 skx = this->skewX;// * layer.texture.scale;
					float64 sky = this->skewY;// * layer.texture.scale;
					this->localTransform.a = sx;
					this->localTransform.b = sx * sky;
					this->localTransform.c = sy * skx;
					this->localTransform.d = sy;
				}
                 */
					this->localTransform.a = sx;
					this->localTransform.b = 0;
					this->localTransform.c = 0;
					this->localTransform.d = sy;
			}
		}
        this->localTransform.tx = this->pos.x;
        this->localTransform.ty = this->pos.y;
        this->localTransform.tz = this->depth;
        this->localTransform.red = this->r;
        this->localTransform.green = this->g;
        this->localTransform.blue = this->b;
        this->localTransform.alpha = this->alpha;
        return this->localTransform;
    }

    Transform& AtlasElement::update_globalTransform()
    {
        if (this->transformMode == TransformMode::GLOBAL) {
			return this->globalTransform.combine_global(this->get_localTransform());
		}
		if (this->transformMode == TransformMode::LOCAL) {
			return this->globalTransform.combine_local(this->get_localTransform(), this->parent->globalTransform);
		}
        return this->globalTransform;
    }


    float64 AtlasElement::set_rotation(float64 value)
    {
        this->dirty = true;
        this->rotation = value;
        if (this->rotation >= 360) this->rotation -= 360;
        else if (this->rotation < 0) this->rotation += 360;
        return this->rotation;
    }
    
    float64 AtlasElement::set_scale(float64 value)
    {
        this->dirty = true;
        return this->scaleX = this->scaleY = value;
    }

    float64 AtlasElement::set_scaleX(float64 value)
    {
        this->dirty = true;
        return this->scaleX = value;
    }

    float64 AtlasElement::set_scaleY(float64 value)
    {
        this->dirty = true;
        return this->scaleY = value;
    }
    
    float64 AtlasElement::rotate(float64 value)
    {
        this->dirty = true;
        this->rotation += value;
        if (this->rotation >= 360) this->rotation -= 360;
        else if (this->rotation < 0) this->rotation += 360;
        return this->rotation;
    }
    
    
    
    /*

    float64 AtlasElement::set_skewX(float64 value)
    {
        this->dirty = true;
        return this->skewX = value;
    }

    float64 AtlasElement::set_skewY(float64 value)
    {
        this->dirty = true;
        return this->skewY = value;
    }
     
     */
    /*
    float64 AtlasElement::set_width(float64 value)
    {
        return this->width;
    }
    
    float64 AtlasElement::set_height(float64 value)
    {
        return this->height;
    }
     */

}
