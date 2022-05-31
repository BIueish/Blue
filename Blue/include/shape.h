#ifndef SHAPE_H
#define SHAPE_H

namespace blue
{
    class Line
    {
    public:
        Line();

        ~Line();

        void draw(int x1, int y1, int x2, int y2, int r, int g, int b, int a=255);

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int shader;
        int v1Loc;
        int v2Loc;
        int colorLoc;
    };

    class Triangle
    {
    public:
        Triangle();
        ~Triangle();

        void draw(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a=255, bool filled=true);

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int shader;
        int v1Loc;
        int v2Loc;
        int v3Loc;
        int colorLoc;
    };

    class Rectangle
    {
    public:
        Rectangle();
        ~Rectangle();

        void draw(int x1, int y1, int width, int height, int r, int g, int b, int a=255, bool filled=true);

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int shader;
        int v1Loc;
        int v2Loc;
        int v3Loc;
        int v4Loc;
        int colorLoc;
    };
}

#endif