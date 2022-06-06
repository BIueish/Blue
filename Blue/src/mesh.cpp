#include "mesh.h"
#include "glad/glad.h"
#include <iostream>

namespace blue
{
    
    void Mesh::setupMesh(std::vector<float> positions, std::vector<unsigned int> indices, std::vector<float> uv, std::vector<float> colors)
    {
        if (indices.size()>1)
            indice = true;
        else
            indice = false;
        if (uv.size()>1)
            texture = true;
        else
            texture = false;
        if (colors.size()>1)
            color = true;
        else
            color = false;

        std::vector<float> data;
        float stride = sizeof(float)*3;
        if (texture)
        {
            stride += sizeof(float)*2;
        }
        count = positions.size();
        for (int i = 0; i < positions.size(); i += 3)
        {
            data.push_back(positions[i]);
            data.push_back(positions[i+1]);
            data.push_back(positions[i+2]);
            if (texture)
            {
                data.push_back(uv[i*2/3]);
                data.push_back(uv[i*2/3+1]);
            }
        }
        if (color)
        {
            stride += sizeof(float)*4;
            for (int i = 0; i < colors.size(); i++)
            {
                data.push_back(colors[i]);
            }
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), &data[0], GL_STATIC_DRAW);

        if (indice)
        {
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);
        size_t offset = sizeof(float)*3;

        if (texture)
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
            offset += 2*sizeof(float);
        }
        if (color)
        {
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (void*)offset);
            offset += 4*sizeof(float);
        }

        glBindVertexArray(0);
    }

    void Mesh::addTexture(const char* path, bool pixel)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int nrComponents;
        int width, height;
        unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            if (pixel)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << "\n";
            stbi_image_free(data);
        }

        textures[texNum] = textureID;
        texNum += 1;
    }

    void Mesh::bindTextures()
    {
        for (int i = 0; i < texNum; i++)
        {
            glActiveTexture(GL_TEXTURE0+i);
            glBindTexture(GL_TEXTURE_2D, textures[i]);
        }
    }
}
