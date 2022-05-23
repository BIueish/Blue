#include "blue.h"
#include "texture.h"
#include <iostream>

int main()
{
    blue::init();
    blue::createWindow("Blue", 600, 600, true);

    blue::Texture texture("./data/grass.png", true);

    while (blue::running())
    {
        blue::clear(255, 255, 255, 255);
        texture.render(300, 300);
        blue::update();
    }

    blue::quit();
}
