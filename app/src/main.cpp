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

    int deg = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    double mx = 0;
    double my = 0;

    blue::hideMouse();

    while (blue::running())
    {
        blue::clear(0, 0, 0, 255);
        mars.render(blue::screenWidth/2-960/2, blue::screenHeight/2-600/2, 960, 600, -30);
        logo.render(blue::screenWidth/2-logo.width/2, blue::screenHeight/2-logo.height/2);
        width = font.draw2D(0, 0, "Blue", 64, 255, 255, 255, 255);
        mouse.render(mx, my, 32, 32);
        test.draw(0, 0, 200, 200, 0, 0, 255);
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

        //deg += 2;
    }

    blue::deinitFonts();
    blue::quit();
}
