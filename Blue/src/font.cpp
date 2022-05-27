#include "font.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace blue
{
    FT_Library ft;

    void initFonts()
    {
        if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not Initialise!\n";
    }

    Font::Font(const char* file, int height)
    {

    }
}
