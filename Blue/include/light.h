#ifndef LIGHT_H
#define LIGHT_H

namespace blue
{
    struct PointLight()
    {
    };

    struct DirectionLight()
    {
        float ix, iy, iz;

        float ax, ay, az;
        float dx, dy, dz;
        float sx, sy, sz;
    };

    struct SpotLight()
    {

    };
}

#endif