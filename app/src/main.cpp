#include "blue.h"
#include "texture.h"
#include "input.h"
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
    double mx = 0;
    double my = 0;

    blue::hideMouse();

    while (blue::running())
    {
        blue::clear(255, 255, 255, 255);
        texture.render(0, 0, -1, -1, deg+45, 1.0f, 1.0f);
        grass.render(mx+x, my+y, 64, 64, deg); 
        blue::update();

        blue::getMousePos(mx, my);

        for (blue::Input key : blue::processEvents())
        {
            if (key.action == BLUE_DOWN || key.action == BLUE_PRESS)
            {
                if (key == "w")
                    y -= 5;
                else if (key == "s")
                    y += 5;
                if (key == "a")
                    x -= 5;
                else if (key == "d")
                    x += 5;
                if (key == "left-button")
                    blue::hideMouse();
                if (key == "escape")
                    blue::showMouse();
            }
        }

        deg += 2;
    }

    blue::quit();
}
