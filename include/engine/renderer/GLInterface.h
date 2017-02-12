#pragma once

namespace Nebula
{
    namespace GL
    {
        typedef GLuint VertexBufferObject;
        typedef GLuint ElementBufferObject;
        typedef GLuint VertexArrayObject;
        typedef GLuint Shader;
        typedef GLuint VertexShader;
        typedef GLuint FragmentShader;
        typedef GLuint ShaderProgram;
        typedef GLuint VertexAttribute;
        typedef GLuint ShaderParam;
        typedef GLuint ElementIndex;
        typedef GLenum Enum;
        typedef GLsizeiptr PtrSize;
        typedef GLuint Texture;

        namespace BufferUploadType
        {
            const Enum STATIC_DRAW = GL_STATIC_DRAW;
            const Enum DYNAMIC_DRAW = GL_DYNAMIC_DRAW;
            const Enum STREAM_DRAW = GL_STREAM_DRAW;
        }

        namespace DataType
        {
            const Enum FLOAT = GL_FLOAT;
            const Enum INT = GL_INT;
            const Enum UNSIGNED_INT = GL_UNSIGNED_INT;
            const Enum BYTE = GL_BYTE;
            const Enum UNSIGNED_BYTE = GL_UNSIGNED_BYTE;
        }

        namespace RenderMode
        {
            const Enum TRIANGLES = GL_TRIANGLES;
            const Enum QUADS = GL_QUADS;
        }
        /*
            GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the world).
            GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
            GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).
            */

        void init();

        void setBlendMode();

        VertexArrayObject createVertexArrayObject();
        void setActiveVertexArrayObject(VertexArrayObject);
        void clearActiveVertexArrayObject();
        void deleteVertexArrayObject(VertexArrayObject*);

        VertexBufferObject createVertexBufferObject();
        void setActiveVertexBufferObject(VertexBufferObject);
        void uploadVertexBufferData(const void*, PtrSize, Enum);
        void clearActiveVertexBufferObject();
        void deleteVertexBufferObject(VertexBufferObject*);

        ElementBufferObject createElementBufferObject();
        void setActiveElementBufferObject(ElementBufferObject);
        void uploadElementBufferData(const void*, PtrSize, Enum);
        void clearActiveElementBufferObject();
        void deleteElementBufferObject(ElementBufferObject*);

        VertexShader createVertexShader();
        FragmentShader createFragmentShader();
        void uploadShaderSource(Shader, std::string);
        void deleteShader(Shader);

        ShaderProgram createShaderProgram(VertexShader, FragmentShader);
        void setActiveShaderProgram(ShaderProgram);
        void clearActiveShaderProgram();
        void deleteShaderProgram(ShaderProgram);

        VertexAttribute createVertexAttribute(ShaderProgram, std::string);
        void enableVertexAttribute(VertexAttribute);
        void disableVertexAttribute(VertexAttribute);
        void defineVertexAttribute(VertexAttribute, void*, int, int, int, std::size_t, Enum, bool);

        ShaderParam createShaderParam(ShaderProgram, std::string);
        void uploadShaderParam(ShaderParam, float);
        void uploadShaderParam(ShaderParam, int);
        void uploadShaderParam(ShaderParam, float, float);
        void uploadShaderParam(ShaderParam, float, float, float);
        void uploadShaderParam(ShaderParam, float, float, float, float);
        void uploadShaderParam(ShaderParam, float, float, float, float);
        void uploadShaderParam(ShaderParam, glm::mat4);

        Texture createTexture();
        void setActiveTexture(unsigned int, Texture);
        void deleteTexture(Texture*);

        void setViewport(int, int, int, int);

        void renderVertices(Enum, int, int);
        void renderElements(Enum, int, int);

        void enableDepthTest();
        void disableDepthTest();

        void clearColorBuffer(float, float, float, float);
        void clearDepthBuffer(float);

        void clearAllActive();
    }
}
