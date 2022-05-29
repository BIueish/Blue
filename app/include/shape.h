#ifndef SHAPE_H
#define SHAPE_H

namespace blue
{
    class Line
    {
    public:
        Line();

        ~Line();

        void draw(int x1, int y1, int x2, int y2, int r, int g, int b);

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int shader;
        int v1Loc;
        int v2Loc;
        int colorLoc;
    };
}

#endif