#ifndef INPUT_H
#define INPUT_H

#include <string>

namespace blue
{

    class Input
    {
    public:
        int key;
        int action;
        int scancode;
        int mods;

        Input(int key, int scancode, int action, int mods) :
            key(key), scancode(scancode), action(action), mods(mods)
        {}

        Input(){};

        const char* name();

        bool operator==(const char* b)
        {
            if (std::string(name()) == std::string(b))
                return true;
            return false;
        }

    };

}

#endif