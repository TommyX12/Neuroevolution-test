#include "engine/includes/utils.h"
//template<typename T>

namespace Nebula
{
    namespace Util
    {
        //std::random_device _rd;
        std::mt19937 _gen(std::chrono::system_clock::now().time_since_epoch().count());
        
        int round(float64 a)
        {
            return std::floor(a + 0.5);
        }

        int64 round64(float64 a)
        {
            return std::floor(a + 0.5);
        }
        
        float64 random(float64 min, float64 max)
        {
            return std::uniform_real_distribution<float64>{min, max}(_gen);
        }
        
        int randomInt(int min, int max)
        {
            return std::uniform_int_distribution<int>{min, max}(_gen);
        }
        
        float64 randomGaussian(float64 mean, float64 standardDeviation)
        {
            return std::normal_distribution<float64>{mean, standardDeviation}(_gen);
        }
        
        int randomSelect(std::vector<float64>& weights)
        {
            float64 total = 0.0;
            int length = weights.size();
            for (int i = 0; i < length; i++){
                total += weights[i];
            }
            
            float64 slice = random(0, total);
            
            float64 current = 0.0;
            for (int i = 0; i < length; i++){
                current += weights[i];
                if (current >= slice){
                    return i;
                }
            }

            return 0;
        }
        
        int maxSelect(std::vector<float64>& weights)
        {
            if (!weights.size()) return -1;
            float64 maxWeight = weights[0];
            float64 maxIndex = 0;
            for (int i = 1; i < weights.size(); i++){
                if (weights[i] > maxWeight) {
                    maxWeight = weights[i];
                    maxIndex = i;
                }
            }
            
            return maxIndex;
        }
        
        float64 clamp(float64 number, float64 min, float64 max)
        {
            if (number < min) return min;
            if (number > max) return max;
            return number;
        }
        
        float64 rotationDistance(float64 start, float64 end)
        {
            const float64 cap = 360, halfCap = 180;
            float64 dif = fmod(end - start, cap);
            if (dif < 0) dif += cap;
            if (dif != fmod(dif, halfCap)) {
                dif = (dif < 0) ? dif + cap : dif - cap;
            }
            return dif;
        }
        
        float64 map(float64 x, float64 in_min, float64 in_max, float64 out_min, float64 out_max)
        {
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }
    }
}
