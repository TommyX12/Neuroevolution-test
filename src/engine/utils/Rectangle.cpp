#include "engine/includes/utils.h"

namespace Nebula
{
    Rectangle::Rectangle()
    : sf::Rect<float64>()
    {
        
    }
    
    Rectangle::Rectangle(float64 x, float64 y, float64 width, float64 height)
    : sf::Rect<float64>(x, y, width, height)
    {
        
    }
    
    Rectangle::contains(Vec2D& point, float64 margin)
    {
        return point.x >= this->left - margin && point.x <= this->left + this->width + margin && point.y >= this->top - margin && point.y <= this->top + this->height + margin;
    }
}
