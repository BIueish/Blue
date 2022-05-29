#include "shape.h"
#include "glad/glad.h"
#include "blue.h"
#include <iostream>

namespace blue
{

    Line::Line()
    {
        float vertices[] = {0.0f, 0.0f,
                            1.0f, 1.0f};

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)0);
        glEnableVertexAttribArray(0);

        unsigned int vertex, fragment;
        const char* vertexSource = "#version 330 core\n\
                                    layout (location = 0) in vec2 pos;\n\
                                    uniform vec2 t1;\n\
                                    uniform vec2 t2;\n\
                                    void main(){\n\
                                    gl_Position = (pos.x == 1) ? vec4(t2, 0.0, 0.0) : vec4(t1, 0.0, 0.0);\n\
                                    }";
        const char* fragmentSource = "#version 330 core\n\
                                      out vec4 fragOut;\n\
                                      uniform vec4 color;\n\
                                      void main(){\n\
                                      fragOut = color;\n\
                                      }";
        vertex = glCreateShader(GL_VERTEX_SHADER);
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex);

        int success;
        char infoLog[1024];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "VERTEX" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }

        glShaderSource(fragment, 1, &fragmentSource, NULL);
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
        v1Loc = glGetUniformLocation(shader, "t1");
        v2Loc = glGetUniformLocation(shader, "t2");
        colorLoc = glGetUniformLocation(shader, "color");

        glUseProgram(0);
        
    }

    Line::~Line()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shader);
        glDeleteVertexArrays(1, &VAO);
    }

    void Line::draw(int x1, int y1, int x2, int y2, int r, int g, int b)
    {
        glBindVertexArray(VAO);
        glUseProgram(shader);

        glUniform2f(v1Loc, (float)x1/screenWidth, (float)y1/screenHeight);
        glUniform2f(v2Loc, (float)x2/screenWidth, (float)y2/screenHeight);
        glUniform4f(colorLoc, (float)r, (float)g, (float)b, 255.0f);

        glDrawArrays(GL_LINES, 0, 2);

        glUseProgram(0);
        glBindVertexArray(0);
    }

}
