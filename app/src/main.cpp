#include "blue.h"
#include "texture.h"
#include "input.h"
#include "font.h"
#include "shape.h"
#include <iostream>

int main()
{
    blue::init();
    blue::createWindow("Blue", 900, 900, true);
    blue::initFonts();

    blue::Texture mars("./data/mars.jpeg");
    blue::Texture logo("./data/logo.png");
    blue::Texture mouse("./data/mouse.png");

    blue::Line test;

    blue::Font font("./data/Roboto.ttf");

    double mx = 0;
    double my = 0;

    blue::hideMouse();

    while (blue::running())
    {
        blue::clear(0, 0, 0, 255);
        mars.render(blue::screenWidth/2-960/2, blue::screenHeight/2-600/2, 960, 600, -30);
        logo.render(blue::screenWidth/2-logo.width/2, blue::screenHeight/2-logo.height/2);
        for (int y = 20; y < blue::screenHeight; y+= 20)
        {
            if (abs(my-y)<=3)
                test.draw(0, y, blue::screenWidth, y, 0, 200, 0, 100);
            else
                test.draw(0, y, blue::screenWidth, y, 0, 200, 0, 50);
        }
        for (int x = 20; x < blue::screenWidth; x+= 20)
        {
            if (abs(mx-x)<=3)
                test.draw(x, 0, x, blue::screenHeight, 0, 200, 0, 100);
            else
                test.draw(x, 0, x, blue::screenHeight, 0, 200, 0, 50);
        }
        font.draw2D(0, 0, "Blue", 64, 255, 255, 255, 255);
        mouse.render(mx, my, 32, 32);
        blue::update();

        blue::getMousePos(mx, my);

        for (blue::Input key : blue::processEvents())
        {
            if (key.action == BLUE_DOWN || key.action == BLUE_PRESS)
            {
                if (key == "left-button")
                    blue::hideMouse();
                if (key == "escape")
                    blue::showMouse();
            }
        }
    }

    blue::deinitFonts();
    blue::quit();
}
