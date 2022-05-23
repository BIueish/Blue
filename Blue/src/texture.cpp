#include "texture.h"
#include "glad/glad.h"
#include <iostream>
#include "blue.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace blue
{
        Texture::Texture(const char* path, bool pixel)
        {
            textureID = loadTexture(path, pixel);
            float vertices[] = {((float)width/screenWidth*2.0f)-1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                ((float)width/screenWidth*2.0f)-1.0f, (-(float)height/screenHeight*2.0f)+1.0f, 0.0f, 1.0f, 1.0f,
                                -1.0f, (-(float)height/screenHeight*2.0f)+1.0f, 0.0f, 0.0f, 1.0f,
                                -1.0f, 1.0f, 0.0f, 0.0f, 0.0f};

            unsigned int indices[] = {0, 1, 3, 1, 2, 3};

            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(sizeof(float)*3));
            glEnableVertexAttribArray(1);

            glBindVertexArray(0);

            unsigned int vertex, fragment;

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vertexShader, NULL);
            glCompileShader(vertex);

            int success;
            char infoLog[1024];
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "VERTEX" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fragmentShader, NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "FRAGMENT" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }

            shader = glCreateProgram();
            glAttachShader(shader, vertex);
            glAttachShader(shader, fragment);
            glLinkProgram(shader);
            
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << "PROGRAM" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            glUseProgram(shader);
            glUniform1i(glGetUniformLocation(shader, "aTexture"), 0);
            glUseProgram(0);

        }

        Texture::~Texture()
        {
            glDeleteTextures(1, &textureID);
            glDeleteProgram(shader);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
        }

        void Texture::render(int x, int y, int dwidth, int dheight)
        {
            glBindVertexArray(VAO);
            glUseProgram(shader);

            glUniform3f(glGetUniformLocation(shader, "translate"), (float)x/screenWidth*2.0f, -(float)y/screenHeight*2.0f, 0.0f);

            if (dheight > -1 && dwidth > -1)
                glUniform3f(glGetUniformLocation(shader, "scale"), (float)dwidth/width, (float)dheight/height, 1.0f);
            else
                glUniform3f(glGetUniformLocation(shader, "scale"), 1.0f, 1.0f, 1.0f);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureID);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glUseProgram(0);
            glBindVertexArray(0);
        }

        unsigned int Texture::loadTexture(const char* path, bool pixel)
        {
            unsigned int textureID;
            glGenTextures(1, &textureID);

            int nrComponents;
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
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }

            return textureID;
        }

}