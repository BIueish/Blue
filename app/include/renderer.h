#ifndef RENDERER_H
#define RENDERER_H

#include "mesh.h"
#include "camera.h"

namespace blue
{

    class Shader
    {
    public:
        unsigned int shader;
        int projectionLoc;
        int modelLoc;
        int viewLoc;
    };

    class Renderer
    {
    public:
        Renderer();
        Shader colorShader;
        Shader textureShader;

        void drawMesh(Mesh& mesh, Camera& camera, Shader shader, float rotx=0.0f, float roty=0.0f, float rotz=0.0f);

        unsigned int loadShader(const char* vertexSource, const char* fragmentSource);
    };
}

#endif