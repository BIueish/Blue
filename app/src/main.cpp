#include "blue.h"
#include "texture.h"
#include <iostream>

int main()
{
    blue::init();
    blue::createWindow("Blue", 600, 600);

    blue::Texture texture("./data/blue.png");

    while (blue::running())
    {
        blue::clear(255, 255, 255, 255);
        texture.render(0, 0);
        blue::update();
    }

    blue::quit();
}
