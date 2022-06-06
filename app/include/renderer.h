#ifndef RENDERER_H
#define RENDERER_H

#include "mesh.h"
#include "camera.h"

namespace blue
{

    class Renderer
    {
    public:
        Renderer();
        unsigned int colorShader;
        unsigned int textureShader;

        void drawMesh(Mesh& mesh, Camera& camera, unsigned int shader, float rotx=0.0f, float roty=0.0f, float rotz=0.0f);
    };
}

#endif