#include "shape.h"
#include "glad/glad.h"
#include "blue.h"
#include <iostream>

namespace blue
{

    Line::Line()
    {
        float vertices[] = {0.0f, 0.0f, 0.0f,
                            1.0f, 1.0f, 0.0f};

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
        glEnableVertexAttribArray(0);

        unsigned int vertex, fragment;
        const char* vertexSource = "#version 330 core\n\
                                    layout (location = 0) in vec3 pos;\n\
                                    uniform vec2 t1;\n\
                                    uniform vec2 t2;\n\
                                    void main(){\n\
                                    gl_Position = (pos.x == 0.0) ? vec4(t1, 0.0, 1.0) : vec4(t2, 0.0, 1.0);\n\
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

    void Line::draw(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
    {
        if (a > 0)
        {
            glBindVertexArray(VAO);
            glUseProgram(shader);

            glUniform2f(v1Loc, ((float)x1/screenWidth*2.0f)-1.0f, (-(float)y1/screenHeight*2.0f)+1.0f);
            glUniform2f(v2Loc, ((float)x2/screenWidth*2.0f)-1.0f, (-(float)y2/screenHeight*2.0f)+1.0f);
            glUniform4f(colorLoc, r/255.0f, g/255.0f, b/255.0f, a/255.0f);


            if (a < 255)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            glDrawArrays(GL_LINES, 0, 2);

            if ( a < 255)
            {
                glDisable(GL_BLEND);
            }

        }

        glUseProgram(0);
        glBindVertexArray(0);
    }

    Triangle::Triangle()
    {
        float vertices[] = {0.0f, 0.0f, 0.0f,
                            1.0f, 1.0f, 0.0f,
                            2.0f, 2.0f, 0.0f};

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
        glEnableVertexAttribArray(0);

        unsigned int vertex, fragment;
        const char* vertexSource = "#version 330 core\n\
                                    layout (location = 0) in vec3 pos;\n\
                                    uniform vec2 t1;\n\
                                    uniform vec2 t2;\n\
                                    uniform vec2 t3;\n\
                                    void main(){\n\
                                    gl_Position = (pos.x == 0.0) ? vec4(t1, 0.0, 1.0) : ((pos.x == 1.0) ? vec4(t2, 0.0, 1.0) : vec4(t3, 0.0, 1.0));\n\
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
        v3Loc = glGetUniformLocation(shader, "t3");
        colorLoc = glGetUniformLocation(shader, "color");

        glUseProgram(0);
    }

    Triangle::~Triangle()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shader);
        glDeleteVertexArrays(1, &VAO);
    }

    void Triangle::draw(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a, bool filled)
    {
        if (a > 0)
        {
            glBindVertexArray(VAO);
            glUseProgram(shader);

            glUniform2f(v1Loc, ((float)x1/screenWidth*2.0f)-1.0f, (-(float)y1/screenHeight*2.0f)+1.0f);
            glUniform2f(v2Loc, ((float)x2/screenWidth*2.0f)-1.0f, (-(float)y2/screenHeight*2.0f)+1.0f);
            glUniform2f(v3Loc, ((float)x3/screenWidth*2.0f)-1.0f, (-(float)y3/screenHeight*2.0f)+1.0f);
            glUniform4f(colorLoc, r/255.0f, g/255.0f, b/255.0f, a/255.0f);

            if (a < 255)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            if (filled)
                glDrawArrays(GL_TRIANGLES, 0, 3);
            else
                glDrawArrays(GL_LINE_LOOP, 0, 3);

            if (a < 255)
            {
                glDisable(GL_BLEND);
            }
        }

        glUseProgram(0);
        glBindVertexArray(0);
    }

    Rectangle::Rectangle()
    {
        float vertices[] = {0.0f, 0.0f, 0.0f,
                            1.0f, 1.0f, 0.0f,
                            2.0f, 2.0f, 0.0f,
                            3.0f, 3.0f, 3.0f,
                            2.0f, 2.0f, 0.0f,
                            0.0f, 0.0f, 0.0f};

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
        glEnableVertexAttribArray(0);

        unsigned int vertex, fragment;
        const char* vertexSource = "#version 330 core\n\
                                    layout (location = 0) in vec3 pos;\n\
                                    uniform vec2 t1;\n\
                                    uniform vec2 t2;\n\
                                    uniform vec2 t3;\n\
                                    uniform vec2 t4;\n\
                                    void main(){\n\
                                    gl_Position = (pos.x == 0.0) ? vec4(t1, 0.0, 1.0) : ((pos.x == 1.0) ? vec4(t2, 0.0, 1.0) : ((pos.x == 2.0) ? vec4(t3, 0.0, 1.0) : vec4(t4, 0.0, 1.0)));\n\
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
        v3Loc = glGetUniformLocation(shader, "t3");
        v4Loc = glGetUniformLocation(shader, "t4");
        colorLoc = glGetUniformLocation(shader, "color");

        glUseProgram(0);
    }

    Rectangle::~Rectangle()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shader);
        glDeleteVertexArrays(1, &VAO);
    }

    void Rectangle::draw(int x1, int y1, int width, int height, int r, int g, int b, int a, bool filled)
    {
        if (a > 0)
        {
            glBindVertexArray(VAO);
            glUseProgram(shader);

            glUniform2f(v1Loc, ((float)x1/screenWidth*2.0f)-1.0f, (-(float)y1/screenHeight*2.0f)+1.0f);
            glUniform2f(v2Loc, ((float)(x1+width)/screenWidth*2.0f)-1.0f, (-(float)y1/screenHeight*2.0f)+1.0f);
            glUniform2f(v3Loc, ((float)(x1+width)/screenWidth*2.0f)-1.0f, (-(float)(y1+height)/screenHeight*2.0f)+1.0f);
            glUniform2f(v4Loc, ((float)x1/screenWidth*2.0f)-1.0f, (-(float)(y1+height)/screenHeight*2.0f)+1.0f);
            glUniform4f(colorLoc, r/255.0f, g/255.0f, b/255.0f, a/255.0f);

            if (a < 255)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            if (filled)
                glDrawArrays(GL_TRIANGLES, 0, 6);
            else
                glDrawArrays(GL_LINE_LOOP, 0, 4);

            if (a < 255)
            {
                glDisable(GL_BLEND);
            }
        }

        glUseProgram(0);
        glBindVertexArray(0);
    }

}
