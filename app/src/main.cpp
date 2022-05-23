#include "blue.h"
#include "texture.h"
#include <iostream>

int main()
{
    blue::init();
    blue::createWindow("Blue", 600, 600, true);

    blue::Texture texture("./data/blue.png");
    blue::Texture grass("./data/grass.png", true);

    int deg = 0;

    while (blue::running())
    {
        blue::clear(255, 255, 255, 255);
        texture.render(0, 0, -1, -1, deg+45, 1.0f, 1.0f);
        grass.render(blue::screenWidth/2, blue::screenHeight/2, 64, 64, deg); 
        blue::update();

        deg += 2;
    }

    blue::quit();
}
