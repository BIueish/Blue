#include "blue.h"
#include "texture.h"
#include "input.h"
#include "font.h"
#include "shape.h"
#include "mesh.h"
#include "renderer.h"
#include "camera.h"
#include <iostream>

int main()
{
    blue::init();
    blue::createWindow("Blue", 900, 900, true);
    blue::initFonts();

    blue::Texture mouse("./data/mouse.png");

    blue::Font font("./data/Roboto.ttf");

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    float uv[] = {
        0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,
     0.0f, 1.0f,
     0.0f, 0.0f,
     1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f};
    

    blue::Renderer renderer;
    blue::Camera camera(0.0f, 0.0f, 3.0f, -90.0f, 0.0f, 0.0f, 70.0f);
    blue::Mesh mesh;
    mesh.setupMesh(std::vector<float>(std::begin(vertices), std::end(vertices)), std::vector<unsigned int>(), std::vector<float>(std::begin(uv), std::end(uv)), std::vector<float>());
    mesh.addTexture("./data/container.png");
    float sensitivity = 5.0f;

    double mx = 0;
    double my = 0;

    int deg = 0;

    blue::lockMouse();

    while (blue::running())
    {
        blue::clear(0, 0, 0, 255);
        font.draw2D(0, 0, "Blue", 64, 255, 255, 255, 255, 0, 0, 255, 100);
        renderer.drawMesh(mesh, camera, renderer.textureShader, 0.0f, 0.0f, 0.0f);
        mouse.render(mx, my, 32, 32);
        blue::update();

        blue::getMousePos(mx, my);

        camera.yaw = -90.0f+(mx-blue::screenWidth/2.0f)/sensitivity;
        camera.pitch = -(my-blue::screenWidth/2.0f)/sensitivity;

        for (blue::Input key : blue::processEvents())
        {
            if (key.action == BLUE_DOWN || key.action == BLUE_PRESS)
            {
                if (key == "left-button")
                    blue::lockMouse();
                if (key == "escape")
                    blue::unlockMouse();
                if (key == "w")
                {
                    camera.y += 0.2f*camera.fy;
                    camera.x += 0.2f*camera.fx;
                    camera.z += 0.2f*camera.fz;
                }
                if (key == "s")
                {
                    camera.y -= 0.2f*camera.fy;
                    camera.x -= 0.2f*camera.fx;
                    camera.z -= 0.2f*camera.fz;
                }
                if (key == "a")
                {
                    camera.y += 0.1f*camera.ry;
                    camera.x += 0.1f*camera.rx;
                    camera.z += 0.1f*camera.rz;
                }
                if (key == "d")
                {
                    camera.y -= 0.1f*camera.ry;
                    camera.x -= 0.1f*camera.rx;
                    camera.z -= 0.1f*camera.rz;
                }
            }
        }
    }

    blue::deinitFonts();
    blue::quit();
}
