#include "key.h"
#include "glfw/glfw3.h"

namespace blue
{

    const char* Key::name()
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
        return glfwGetKeyName(key, scancode);
    }

}
