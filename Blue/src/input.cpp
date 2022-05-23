#include "input.h"
#include "glfw/glfw3.h"

namespace blue
{

    const char* Input::name()
    {
        if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
            return "shift";
        else if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
            return "control";
        else if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
            return "alt";
        else if (key == GLFW_KEY_LEFT_SUPER || key == GLFW_KEY_RIGHT_SUPER)
            return "os-key";
        else if (key == GLFW_KEY_BACKSPACE)
            return "backspace";
        else if (key == GLFW_KEY_ENTER)
            return "enter";
        else if (key == GLFW_KEY_TAB)
            return "tab";
        else if (key == GLFW_KEY_CAPS_LOCK)
            return "caps-lock";
        else if (key == GLFW_KEY_ESCAPE)
            return "escape";
        else if (key == GLFW_MOUSE_BUTTON_LEFT)
            return "left-button";
        else if (key == GLFW_MOUSE_BUTTON_RIGHT)
            return "right-button";
        else if (key == GLFW_MOUSE_BUTTON_MIDDLE)
            return "middle-button";
        else if (key == GLFW_KEY_LEFT)
            return "left";
        else if (key == GLFW_KEY_RIGHT)
            return "right";
        else if (key == GLFW_KEY_UP)
            return "up";
        else if (key == GLFW_KEY_DOWN)
            return "down";
        return glfwGetKeyName(key, scancode);
    }

}
