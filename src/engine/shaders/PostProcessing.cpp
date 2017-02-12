#include "engine/includes/shaders.h"

namespace Nebula
{
    namespace Shader
    {
        std::string invertColor()
        {
            std::ostringstream strStream;
            strStream <<
            //"#version 330\n"
            "uniform float time;"
            "uniform sampler2D texture;"
            "uniform vec2 resolution;"
            ""
            "void main()"
            "{"
            "vec2 position = gl_FragCoord.xy / resolution;"
            "gl_FragColor = texture2D(texture, position);"
            "}";
            return strStream.str();
        }

        std::string frag_test()
        {
            //char szbuffer[32];
            std::ostringstream strStream;
            strStream <<
            //"#version 330\n"
            "void main()"
            "{"
            "gl_FragColor = vec4(gl_TexCoord[0].xy, 1.0, 1.0);"
            //"gl_FragColor = texture2D(current, position / resolution) + 0.5;"
            "}";
            return strStream.str();
        }

        std::string vert_velocityBuffer()
        {

            char szbuffer[32];

            std::ostringstream strStream;
            strStream <<
            //"#version 330\n"
            "uniform float scale;"
            "uniform vec2 scaleOffset;"
            "varying vec2 textureCoord;"
            "varying vec2 quadIndex;"
            "";
            sprintf(szbuffer, "%.16lf", (float64)1.0 / 256.0);
            strStream << "const float b = " << szbuffer << ";"
            ""
            "void main()"
            "{"
            "gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
            "gl_Position.xy = gl_Position.xy * scale - scaleOffset;"
            "gl_TexCoord[0] = gl_MultiTexCoord0 * scale;"
            //"gl_TexCoord[0].xy = vec2(0.0);"
            "textureCoord = vec2(gl_Color.r+gl_Color.g*b, gl_Color.b+gl_Color.a*b);"
            "int quadID = gl_VertexID / 2;"
            "int quadIDA = quadID / 256;"
            "int quadIDB = quadID - (256 * quadIDA);"
            "quadIndex = vec2(float(quadIDA) / 255.0, float(quadIDB) / 255.0);"
            "gl_FrontColor = gl_Color;"
            "}";
            return strStream.str();
        }

        std::string frag_velocityBuffer()
        {
            //char szbuffer[32];
            std::ostringstream strStream;
            strStream <<
            //"#version 330\n"
            "uniform float time;"
            "uniform vec2 resolution;"
            "uniform float velMul;"
            "uniform sampler2D current;"
            "varying vec2 textureCoord;"
            "varying vec2 quadIndex;"
            "void main()"
            "{"
            "vec2 position = gl_FragCoord.xy;"
            "position.y = resolution.y - position.y;"
            "if (texture2D(current, textureCoord).a < 0.01) discard;"
            //"gl_FragColor = texture2D(current, texCoord);"
            //"gl_FragColor = vec4(texCoord, 0.0, 1.0);"
            //"gl_FragColor = vec4(gl_TexCoord[0].xy / resolution, 0.0, 1.0);"
            //"gl_FragColor = vec4(0.5, 0.0, 0.0, 1.0);"
            //"gl_FragColor = texture2D(current, position / resolution) + 0.5;"
            "gl_FragColor = vec4((position.xy - gl_TexCoord[0].xy) * velMul * vec2(1.0, -1.0) + 0.5, quadIndex.x, 1.0);"
            "}";
            return strStream.str();
        }

        std::string frag_velocityExpand()
        {
            std::ostringstream strStream;
            strStream <<
            //"#version 330\n"
            "uniform sampler2D current;"
            "uniform vec2 resolution;"
            ""
            "void main()"
            "{"
            "vec2 position = gl_TexCoord[0].xy;"
            "gl_FragColor = texture2D(current, position);"
            "vec4 _depth = gl_FragColor;"
            "vec2 res = 1.0 / resolution;"
            "float currentDepth = _depth.b * 1000.0 + _depth.a;"
            "_depth = texture2D(current, position + vec2(8.0, 0.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "_depth = texture2D(current, position + vec2(-8.0, 0.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "_depth = texture2D(current, position + vec2(0.0, 8.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "_depth = texture2D(current, position + vec2(0.0, -8.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "_depth = texture2D(current, position + vec2(3.0, 3.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "_depth = texture2D(current, position + vec2(-3.0, 3.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "_depth = texture2D(current, position + vec2(3.0, -3.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "_depth = texture2D(current, position + vec2(-3.0, -3.0) * res);"
            "if (_depth.b * 1000.0 + _depth.a > currentDepth) gl_FragColor.rg = _depth.rg;"
            "}";
            return strStream.str();
        }

        std::string frag_motionBlur(int sampleCount)
        {
            char szbuffer[32];
            std::ostringstream strStream;
            strStream <<
            //"#version 330\n"
            "uniform float stepMul;"
            "uniform vec2 resolution;"
            "uniform sampler2D current;"
            "uniform sampler2D velocity;"
            ""
            "void main()"
            "{"
            "vec3 color = vec3(0.0);"
            "vec2 vel = texture2D(velocity, gl_TexCoord[0].xy).rg - 0.5;"
            "vec2 position = gl_FragCoord.xy;"
            "vec2 res = 1.0 / resolution;";
            for (int i = 0; i < sampleCount; i++){
                sprintf(szbuffer, "%d", i);
                strStream << "color += texture2D(current, (position + vel * " << szbuffer << ".0 * stepMul) * res).rgb;";
            }
            sprintf(szbuffer, "%.16lf", 1.0 / sampleCount);
            strStream << "gl_FragColor = vec4(color * " << szbuffer << ", 1.0);"
            //"gl_FragColor = vec4(vel, 0.0, 1.0);"
            "}";
            return strStream.str();
        }
    }
}
