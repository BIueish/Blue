#ifndef FONT_H
#define FONT_H

namespace blue
{
    void initFonts();

    class Font
    {
        Font(const char* file, int height);
    };

}

#endif