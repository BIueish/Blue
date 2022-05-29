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

        void draw2D(int x, int y, const char* text, int height);

        int height;

    private:
        int index;
    };

}

#endif