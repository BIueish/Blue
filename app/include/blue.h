#ifndef BLUE_H
#define BLUE_H

namespace blue
{
    extern int screenWidth;
    extern int screenHeight;

    void print();
    void init();
    void createWindow(const char* title, int width, int height, bool adjust=false);
    void quit();
    void clear(int r, int g, int b, int a);
    void update();
    bool running();
    void onWindowResize(int width, int height);
}

#endif