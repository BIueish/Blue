#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace blue
{
    Camera::Camera(float x, float y, float z, float yaw, float pitch, float roll, float fov) :
    x(x), y(y), z(z), yaw(yaw), pitch(pitch), roll(roll), fov(fov)
    {}

    void Camera::calculate()
    {
        fx = cos(glm::radians(yaw))*cos(glm::radians(pitch));
        fy = sin(glm::radians(pitch));
        fz = sin(glm::radians(yaw))*cos(glm::radians(pitch));
        glm::vec3 front = glm::normalize(glm::vec3(fx, fy, fz));
        fx = front.x;
        fy = front.y;
        fz = front.z;
    }
}
