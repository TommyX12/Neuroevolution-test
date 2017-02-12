#pragma once


namespace Nebula
{
    class Rectangle: public sf::Rect<float64>
    {
    public:
        Rectangle();
        Rectangle(float64, float64, float64, float64);
        contains(Vec2D&, float64);
    protected:
    private:
    };
}
