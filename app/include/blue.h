#ifndef BLUE_H
#define BLUE_H
#include "key.h"
#include <vector>

#define BLUE_KEYDOWN 1
#define BLUE_KEYUP 0
#define BLUE_KEYPRESS 2
#define BLUE_MODSHIFT 1
#define BLUE_MODCTRL 2
#define BLUE_MODALT 4
#define BLUE_MODOS 8
#define BLUE_MODCAPS 10

namespace blue
{
    extern int screenWidth;
    extern int screenHeight;

    void print();
    void init();
    std::vector<Key> processKeys(bool keep=false);
    void createWindow(const char* title, int width, int height, bool adjust=false);
    void quit();
    void clear(int r, int g, int b, int a);
    void update();
    bool running();
    void onWindowResize(int width, int height);
}

#endif