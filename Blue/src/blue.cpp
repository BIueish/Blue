#include "blue.h"
#include "key.h"
#include "texture.cpp"
#include "key.cpp"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <iostream>

GLFWwindow* window = nullptr;

namespace blue
{
    int screenWidth;
    int screenHeight;

    bool adjustWindow;

    std::vector<Key> keys;

    std::vector<Key> processKeys(bool keep)
    {
        std::vector<Key> inputKeys = keys;
        if (!keep)
            keys.clear();
        return inputKeys;
    }

    void framebufferResize(GLFWwindow* window, int width, int height);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        keys.push_back(Key(key, scancode, action, mods));
    }

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
        glfwSetKeyCallback(window, keyCallback);
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
        if (adjustWindow)
        {
            screenWidth = width/2;
            screenHeight = height/2;
        }
        else
        {
            screenWidth = width;
            screenHeight = height;
        }
    }
}
