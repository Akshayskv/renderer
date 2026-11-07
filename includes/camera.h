#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
    explicit Camera(float aspectRatio, glm::vec3 position = {0.0f, 0.0f, 0.0f}, float fovDegrees = 75.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
    void move(glm::vec3 localDir, float dt);
    void setPosition(glm::vec3 p);
    void setRotation(float yaw, float pitch);
    void setFov(float degrees);
    void setClipPlanes(float nearPlane, float farPlane);
    void setAspectRatio(float ratio);
    void setSpeed(float s);

    const glm::mat4& getView() const;
    const glm::mat4& getProjection() const;
    const glm::mat4& getViewProjection() const;

private:
    void calculateViewProjection() const;

    glm::vec3 position{0.0f};
    float yaw = -90.0f, pitch = 0.0f;
    float speed = 1.0f;
    float fov, nearPlane, farPlane, aspectRatio;

    mutable bool dirty = true;
    mutable glm::mat4 view{1.0f}, projection{1.0f}, viewProjection{1.0f};
};
#endif