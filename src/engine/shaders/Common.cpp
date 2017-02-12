#include "engine/includes/shaders.h"

namespace Nebula
{
    namespace Shader
    {
        std::string vert_default()
        {
            std::ostringstream strStream;
            strStream <<
                //"#version 330\n"
                "attribute vec3 positionIn;"
                "attribute vec4 colorIn;"
                "attribute vec2 texCoordIn;"
                //"varying vec2 position;"
                "varying vec4 color;"
                "varying vec2 texCoord;"
                "uniform mat4 matModel;"
                "uniform mat4 matView;"
                "uniform mat4 matProjection;"
                ""
                "void main()"
                "{"
                "color = colorIn;"
                "texCoord = texCoordIn;"
                //"position = positionIn;"
                "gl_Position = matProjection * matView * matModel * vec4(positionIn, 1.0);"
                "}";
            return strStream.str();
        }

        std::string frag_default()
        {
            std::ostringstream strStream;
            strStream <<
                //"#version 330\n"
                "uniform float time;"
                "uniform sampler2D texture_battleship;"
                "uniform sampler2D texture_opengl;"
                //"varying vec2 position;"
                "varying vec4 color;"
                "varying vec2 texCoord;"
                ""
                "void main()"
                "{"
                "gl_FragColor = texture2D(texture_battleship, texCoord) * color + texture2D(texture_opengl, texCoord);"
                "}";
            return strStream.str();
        }
    }
}
