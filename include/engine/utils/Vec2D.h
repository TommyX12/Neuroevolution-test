#pragma once
namespace Nebula
{
    class Vec2D
    {
        public:
            float64 x, y;
            Vec2D();
            Vec2D(float64, float64);
            virtual ~Vec2D();
            Vec2D operator+(const Vec2D&);
            Vec2D operator-(const Vec2D&);
            Vec2D operator*(float64);
            Vec2D operator/(float64);
            Vec2D& operator=(const Vec2D&);
            bool operator==(const Vec2D&);
            Vec2D& operator+=(const Vec2D&);
            Vec2D& operator-=(const Vec2D&);
            Vec2D& operator*=(float64);
            Vec2D& operator/=(float64);
            Vec2D& reset();
            float64 distance(const Vec2D&);
            float64 length();
            float64 lengthSq();
            float64 angle();
            float64 angleTo(const Vec2D&);
            float64 distanceSq(const Vec2D&);
            Vec2D& addDirectional(float64, float64);
            Vec2D& rotate(float64);
        protected:
        private:
    };
}
