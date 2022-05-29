#include "font.h"
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "msdfgl.h"
#include "glm/glm.hpp"
#include "blue.h"

namespace blue
{
    msdfgl_context_t context;

    std::vector<msdfgl_font_t> fonts; 

    void initFonts()
    {
        context = msdfgl_create_context("330 core");

        if (!context)
            std::cout << "ERROR::FONT: Failed to initialise fonts!\n";

        /* Enable auto-generating undefined glyphs as they are encountered for the first time. */
        msdfgl_set_missing_glyph_callback(context, msdfgl_generate_glyph, NULL);
    }

    void deinitFonts()
    {
        msdfgl_destroy_context(context);
    }

    Font::Font(const char* file)
    {
        fonts.push_back(msdfgl_load_font(context, file, 4.0, 2.0, NULL));
        index = fonts.size()-1;

        if (!fonts[index])
            std::cout << "ERROR::FONT: Failed to load font: " << file << '\n';

        //font = msdfgl_load_font(context, file, 4.0, 2.0, NULL); /* range, scale, atlas (NULL creates a new one) */

        /* Loads characters 0-128 onto the textures. This is where all the GPU cycles went. */
        msdfgl_generate_ascii(fonts[index]);
    }

    Font::~Font()
    {
        //msdfgl_destroy_font(fonts[index]);
        free(fonts[index]);
    }

    int Font::draw2D(int x, int y, const char* text, int height, int r, int g, int b, int a)
    {
        GLfloat projection[4][4];

        _msdfgl_ortho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f, projection);

        /*            x    y           size  color       4x4 projection-matrix  flags */
        unsigned int color = (unsigned int)((glm::floor(r/16)*256*256*256*16)+((r%16)*256*256*256)+(glm::floor(g/16)*256*256*16)+((g%16)*256*256)+(glm::floor(b/16)*256*16)+((b%16)*256)+(glm::floor(a/16)*16)+(a%16));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        float x1 = msdfgl_printf((float)x, (float)(y+height), fonts[index], (float)height, color, (GLfloat *)projection, MSDFGL_KERNING,
                    text, MSDFGL_VERSION);
        glDisable(GL_BLEND);

        return x1-x;
    }
}
