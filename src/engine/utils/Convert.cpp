#include "engine/includes/utils.h"

namespace Nebula
{
    namespace Convert
    {
        float64 rad(float64 deg)
        {
            return (float64)deg / 180.0 * PI;
        }

        float64 deg(float64 rad)
        {
            return (float64)rad / PI * 180.0;
        }
    }
}
