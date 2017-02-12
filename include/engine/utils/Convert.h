#pragma once
namespace Nebula
{
    namespace Convert
    {
        float64 rad(float64);
        float64 deg(float64);
        
        template<typename T>
        std::string str(T value)
        {
            std::ostringstream stream;
            stream << value;
            return stream.str();
        }
    }
}
