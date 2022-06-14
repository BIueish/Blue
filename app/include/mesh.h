#ifndef MESH_H
#define MESH_H

#include <vector>

namespace blue
{
    class Mesh
    {
    public:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        bool indice;
        bool color;
        bool texture;
        int count;
        unsigned int textures[16];
        int texNum = 0;
        
        void setupMesh(std::vector<float> positions, std::vector<unsigned int> indices, std::vector<float> uv, std::vector<float> colors);
        void addTexture(const char* path, bool pixel=false);
        void bindTextures();
    };
}

#endif