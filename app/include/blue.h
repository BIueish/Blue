namespace blue
{
    extern int screenWidth;
    extern int screenHeight;

    void print();
    void init();
    void createWindow(const char* title, int width, int height);
    void quit();
    void clear(int r, int g, int b, int a);
    void update();
    bool running();
    
}