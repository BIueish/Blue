#ifndef KEY_H
#define KEY_H

#include <string>

namespace blue
{

    class Key
    {
    public:
        int key;
        int action;
        int scancode;
        int mods;

        Key(int key, int scancode, int action, int mods) :
            key(key), scancode(scancode), action(action), mods(mods)
        {}

        Key(){};

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