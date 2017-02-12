#include "engine/includes/renderer.h"

namespace Nebula
{
    namespace GL
    {

        void init()
        {
            //opengl init
            //glewExperimental = GL_TRUE;
            //glewInit();
        }

        void setBlendMode()
        {
            glEnable(GL_BLEND); //enable blending
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set as alpha blending
        }

        VertexArrayObject createVertexArrayObject()
        {
            VertexArrayObject vao = 0;
#ifdef OSX
            glGenVertexArraysAPPLE(1, &vao);
#endif
#ifdef WINDOWS
            if (GLEW_ARB_vertex_array_object){
                glGenVertexArrays(1, &vao);
            }
#endif
            return vao;
        }

        void setActiveVertexArrayObject(VertexArrayObject vao)
        {
#ifdef OSX
            glBindVertexArrayAPPLE(vao);
#endif
#ifdef WINDOWS
            if (GLEW_ARB_vertex_array_object){
                glBindVertexArray(vao);
            }
#endif
        }

        void clearActiveVertexArrayObject()
        {
#ifdef OSX
            glBindVertexArrayAPPLE(0);
#endif
#ifdef WINDOWS
            if (GLEW_ARB_vertex_array_object){
                glBindVertexArray(0);
            }
#endif
        }

        void deleteVertexArrayObject(VertexArrayObject* vao)
        {
#ifdef OSX
            glDeleteVertexArraysAPPLE(1, vao);
#endif
#ifdef WINDOWS
            if (GLEW_ARB_vertex_array_object){
                glDeleteVertexArrays(1, vao);
            }
#endif
        }

        VertexBufferObject createVertexBufferObject()
        {
            VertexBufferObject vbo; //container of vertex data
            glGenBuffers(1, &vbo);

            return vbo;
        }

        void setActiveVertexBufferObject(VertexBufferObject vbo)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
        }

        void uploadVertexBufferData(const void* data, PtrSize size, Enum type) //to active buffer object
        {
            glBufferData(GL_ARRAY_BUFFER, size, data, type);
        }

        void clearActiveVertexBufferObject()
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void deleteVertexBufferObject(VertexBufferObject* vbo)
        {
            glDeleteBuffers(1, vbo);
        }

        ElementBufferObject createElementBufferObject()
        {
            ElementBufferObject ebo; //container of vertex data
            glGenBuffers(1, &ebo);

            return ebo;
        }

        void setActiveElementBufferObject(ElementBufferObject ebo)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        }

        void uploadElementBufferData(const void* data, PtrSize size, Enum type) //to active buffer object
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, type);
        }

        void clearActiveElementBufferObject()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void deleteElementBufferObject(ElementBufferObject* ebo)
        {
            glDeleteBuffers(1, ebo);
        }

        VertexShader createVertexShader()
        {
            return glCreateShader(GL_VERTEX_SHADER);
        }

        FragmentShader createFragmentShader()
        {
            return glCreateShader(GL_FRAGMENT_SHADER);
        }

        void uploadShaderSource(Shader shader, std::string source)
        {
            const char *shaderSrc = source.c_str();
            glShaderSource(shader, 1, &shaderSrc, null); //upload shader from source to shader, stop at null termination
            glCompileShader(shader);
        }

        void deleteShader(Shader shader)
        {
            glDeleteShader(shader);
        }

        ShaderProgram createShaderProgram(VertexShader vertexShader, FragmentShader fragmentShader)
        {
            ShaderProgram shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            //glBindFragDataLocation(shaderProgram, 0, "colorOut");
            glLinkProgram(shaderProgram);

            return shaderProgram;
        }

        void setActiveShaderProgram(ShaderProgram shaderProgram)
        {
            glUseProgram(shaderProgram);
        }

        void clearActiveShaderProgram()
        {
            glUseProgram(0);
        }

        void deleteShaderProgram(ShaderProgram shaderProgram)
        {
            glDeleteProgram(shaderProgram);
        }

        VertexAttribute createVertexAttribute(ShaderProgram shaderProgram, std::string name)
        {
            return glGetAttribLocation(shaderProgram, name.c_str());
        }

        void enableVertexAttribute(VertexAttribute vertexAttribute)
        {
            glEnableVertexAttribArray(vertexAttribute);
        }

        void diableVertexAttribute(VertexAttribute vertexAttribute)
        {
            glDisableVertexAttribArray(vertexAttribute);
        }

        void defineVertexAttribute(VertexAttribute vertexAttribute, void* pointerToArray, int numElementPerVertexInCurrentArray, int numElementInAttribute, int startingIndexOfAttribute, std::size_t sizeOfElement, Enum glDataType, bool normalized)
        {
            //leave pointerToArray to 0 to use current VBO.
            /*
            Specify how the array of numbers in vertex data should be interpreted. Each attribute is a part of the data for each vert.
            Arguments:
                Attribute
                number of values
                type of each value
                normalized(if true, integer types will be mapped from 0 - MAX to 0 - 1, or if signed -MAX - MAX to -1 - 1)
                number of total attribute for each vert. if no vbo, number of bytes between occurence of this attribute.
                starting byte of first occurence
            */
            /*
                if vertex buffer object is disabled (cleared), pointer can refer to absolute pointer in cpu, which can use diff arrays for diff attributes.
            */
            /*glVertexAttribPointer(<#GLuint index#>, <#GLint size#>, <#GLenum type#>, <#GLboolean normalized#>, <#GLsizei stride#>, <#const GLvoid *pointer#>)*/
#ifdef OSX
            glVertexAttribPointer((GLuint)vertexAttribute, (GLint)numElementInAttribute, (GLenum)glDataType, normalized, (GLsizei)numElementPerVertexInCurrentArray * sizeOfElement, (GLvoid*)(startingIndexOfAttribute * sizeOfElement));
#endif
#ifdef WINDOWS
            glVertexAttribPointer(vertexAttribute, numElementInAttribute, glDataType, normalized, numElementPerVertexInCurrentArray * sizeOfElement, (startingIndexOfAttribute * sizeOfElement) + pointerToArray);
#endif
        }

        ShaderParam createShaderParam(ShaderParam shaderProgram, std::string name)
        {
            return glGetUniformLocation(shaderProgram, name.c_str());
        }

        void uploadShaderParam(ShaderParam shaderParam, int value1)
        {
            glUniform1i(shaderParam, value1);
        }

        void uploadShaderParam(ShaderParam shaderParam, float value1)
        {
            glUniform1f(shaderParam, value1);
        }

        void uploadShaderParam(ShaderParam shaderParam, float value1, float value2)
        {
            glUniform2f(shaderParam, value1, value2);
        }

        void uploadShaderParam(ShaderParam shaderParam, float value1, float value2, float value3)
        {
            glUniform3f(shaderParam, value1, value2, value3);
        }

        void uploadShaderParam(ShaderParam shaderParam, float value1, float value2, float value3, float value4)
        {
            glUniform4f(shaderParam, value1, value2, value3, value4);
        }

        void uploadShaderParam(ShaderParam shaderParam, glm::mat4 matrix)
        {
            glUniformMatrix4fv(shaderParam, 1, false, glm::value_ptr(matrix));
        }

        Texture createTexture()
        {
            Texture texture;
            glGenTextures(1, &texture);

            return texture;
        }

        void setActiveTexture(unsigned int textureSlot, Texture texture)
        {
            glActiveTexture(GL_TEXTURE0 + textureSlot);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void deleteTexture(Texture* texture)
        {
            glDeleteTextures(1, texture);
        }

        void setViewport(int x, int y, int width, int height)
        {
            glViewport(x, y, width, height);
        }

        void renderVertices(Enum mode, int start, int count)
        {
            glDrawArrays(mode, start, count);
        }

        void renderElements(Enum mode, const void* start, int count, Enum elementDataType)
        {
            glDrawElements(mode, count, elementDataType, start);
        }

        void enableDepthTest()
        {
            glEnable(GL_DEPTH_TEST);
        }

        void  disableDepthTest()
        {
            glDisable(GL_DEPTH_TEST);
        }

        void clearColorBuffer(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a); //set color
            glClear(GL_COLOR_BUFFER_BIT); //clear
        }

        void clearDepthBuffer(float depth)
        {
            glClearDepth(depth); //set depth
            glClear(GL_DEPTH_BUFFER_BIT); //clear
        }

        void clearAllActive()
        {
            clearActiveVertexArrayObject();
            clearActiveVertexBufferObject();
            clearActiveElementBufferObject();
            clearActiveShaderProgram();
        }
    }
}
