#include "blue.h"

int main()
{
    blue::print();
    blue::init();
    blue::createWindow("Blue", 600, 600);

    while (blue::running())
    {
        blue::clear(0, 0, 255, 255);
        blue::update();
    }

    blue::quit();
}
