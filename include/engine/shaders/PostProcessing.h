#pragma once

namespace Nebula
{
    namespace Shader
    {
        std::string invertColor();
        std::string vert_velocityBuffer();
        std::string frag_velocityBuffer();
        std::string frag_velocityExpand();
        std::string frag_motionBlur(int);
        std::string frag_test();
    }
}
