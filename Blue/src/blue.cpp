#include "blue.h"
#include "texture.cpp"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <iostream>

GLFWwindow* window = nullptr;

namespace blue
{
    int screenWidth;
    int screenHeight;

    bool adjustWindow;

    void framebufferResize(GLFWwindow* window, int width, int height);
    void onWindowResize(int width, int height){};

    void print()
    {
        std::cout << "Welcome to Blue!\n";
    }

    void init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    void createWindow(const char* title, int width, int height, bool adjust)
    {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        glfwMakeContextCurrent(window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (adjust)
            glViewport(0, 0, width*2, height*2);
        else
            glViewport(0, 0, width, height);
        screenWidth = width;
        screenHeight = height;
        adjustWindow = adjust;

        glfwSetFramebufferSizeCallback(window, framebufferResize);
    }

    void clear(int r, int g, int b, int a = 255)
    {
        r /= 255;
        g /= 255;
        b /= 255;
        a /= 255;

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void update()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void quit()
    {
        glfwTerminate();
    }

    bool running()
    {
        return !glfwWindowShouldClose(window);
    }

    void framebufferResize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        screenWidth = width/2;
        screenHeight = height/2;
        onWindowResize(width, height);
    }
}
