#include "blue.h"
#include "input.h"
#include "texture.cpp"
#include "input.cpp"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <iostream>

GLFWwindow* window = nullptr;

namespace blue
{
    int screenWidth;
    int screenHeight;

    bool adjustWindow;

    std::vector<Input> events;

    std::vector<Input> processEvents(bool keep)
    {
        std::vector<Input> inputEvents = events;
        if (!keep)
            events.clear();
        return inputEvents;
    }

    void getMousePos(double& x, double& y)
    {
        glfwGetCursorPos(window, &x, &y);
    }

    void hideMouse(){ glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);}
    void showMouse(){ glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}

    void lockMouse(){ glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);}
    void unlockMouse(){ glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}

    bool mouseHover(){ return glfwGetWindowAttrib(window, GLFW_HOVERED);}

    void framebufferResize(GLFWwindow* window, int width, int height);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        events.push_back(Input(key, scancode, action, mods));
    }
    void mouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
        events.push_back(Input(button, 0, action, mods));
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
        glfwSetMouseButtonCallback(window, mouseCallback);
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
