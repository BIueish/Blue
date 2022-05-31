#ifndef FONT_H
#define FONT_H

namespace blue
{
    void initFonts();
    void deinitFonts();

    class Font
    {
    public:
        Font(const char* file);

        ~Font();

        int draw2D(int x, int y, const char* text, int height, int r, int g, int b, int a=255, int br=0, int bg=0, int bb=0, int ba=0);

        int height;

    private:
        int index;
    };

}

#endif