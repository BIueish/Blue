#ifndef CAMERA_H
#define CAMERA_H

namespace blue
{
    class Camera
    {
    public:
        float x, y, z;
        float yaw, pitch, roll;
        float fov;
        float fx, fy, fz;

        Camera(float x, float y, float z, float yaw, float pitch, float roll, float fov);
        void calculate();
    };
}

#endif