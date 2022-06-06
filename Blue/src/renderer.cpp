#include "renderer.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "blue.h"
#include "camera.h"

namespace blue
{
    Renderer::Renderer()
    {
        const char* vertexSource = "#version 330 core\n\
                                    layout (location = 0) in vec3 pos;\n\
                                    uniform mat4 projection;\n\
                                    uniform mat4 model;\n\
                                    uniform mat4 view;\n\
                                    void main(){\n\
                                    gl_Position = projection*view*model*vec4(pos, 1.0f);\n\
                                    }";
        const char* fragmentSource = "#version 330 core\n\
                                    out vec4 fragOut;\n\
                                    void main(){\n\
                                    fragOut = vec4(0.0, 1.0, 1.0, 1.0);\n\
                                    }";

        colorShader = loadShader(vertexSource, fragmentSource);

        vertexSource = "#version 330 core\n\
                        layout (location = 0) in vec3 pos;\n\
                        layout (location = 1) in vec2 tex;\n\
                        out vec2 texPos;\n\
                        uniform mat4 projection;\n\
                        uniform mat4 model;\n\
                        uniform mat4 view;\n\
                        void main(){\n\
                        gl_Position = projection*view*model*vec4(pos, 1.0f);\n\
                        texPos = tex;\n\
                        }";
        fragmentSource = "#version 330 core\n\
                          out vec4 fragOut;\n\
                          in vec2 texPos;\n\
                          uniform sampler2D tex;\n\
                          void main(){\n\
                          fragOut = texture(tex, texPos);\n\
                          }";
        textureShader = loadShader(vertexSource, fragmentSource);
        glUseProgram(textureShader);
        glUniform1i(glGetUniformLocation(textureShader, "tex"), 0);
        glUseProgram(0);
    }

    void Renderer::drawMesh(Mesh& mesh, Camera& camera, unsigned int shader, float rotx, float roty , float rotz)
    {
        glBindVertexArray(mesh.VAO);
        glUseProgram(shader);
        mesh.bindTextures();
        glm::mat4 proj(1.0f);
        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        camera.calculate();
        proj = glm::perspective(camera.fov, (float)screenWidth/screenHeight, 0.1f, 100.0f);
        view = glm::lookAt(glm::vec3(camera.x, camera.y, camera.z), glm::vec3(camera.x+camera.fx, camera.y+camera.fy, camera.z+camera.fz), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotx), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(roty), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotz), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        if (mesh.indice)
        {
            
        }
        else
        {

            glDrawArrays(GL_TRIANGLES, 0, mesh.count);
        }

        glUseProgram(0);
        glBindVertexArray(0);
    }

    unsigned int Renderer::loadShader(const char* vertexSource, const char* fragmentSource)
    {
        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertex, 1, &vertexSource, NULL);
        glShaderSource(fragment, 1, &fragmentSource, NULL);

        glCompileShader(vertex);
        int success;
        char infoLog[1024];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "VERTEX" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        glCompileShader(fragment);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "FRAGMENT" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }

        unsigned int shader = glCreateProgram();
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

        return shader;
    }
}
