#pragma once


//template<typename T>
namespace Nebula
{
    namespace Util
    {
        extern std::mt19937 _gen;
        
        int round(float64);
        int64 round64(float64);
        float64 random(float64, float64);
        int randomInt(int, int);
        float64 randomGaussian(float64, float64);
        int randomSelect(std::vector<float64>&);
        int maxSelect(std::vector<float64>&);
        float64 clamp(float64, float64, float64);
        float64 rotationDistance(float64, float64);
        float64 map(float64, float64, float64, float64, float64);
    }
}
