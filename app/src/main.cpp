#include "blue.h"
#include "texture.h"
#include "key.h"
#include <iostream>

int main()
{
    blue::init();
    blue::createWindow("Blue", 600, 600, true);

    blue::Texture texture("./data/blue.png");
    blue::Texture grass("./data/grass.png", true);

    int deg = 0;
    int x = 0;
    int y = 0;

    while (blue::running())
    {
        blue::clear(255, 255, 255, 255);
        texture.render(0, 0, -1, -1, deg+45, 1.0f, 1.0f);
        grass.render(blue::screenWidth/2+x, blue::screenHeight/2+y, 64, 64, deg); 
        blue::update();

        for (blue::Key key : blue::processKeys())
        {
            if (key.action == BLUE_KEYDOWN || key.action == BLUE_KEYPRESS)
            {
                if (key == "w")
                    y -= 5;
                else if (key == "s")
                    y += 5;
                if (key == "a")
                    x -= 5;
                else if (key == "d")
                    x += 5;
            }
        }

        deg += 2;
    }

    blue::quit();
}
