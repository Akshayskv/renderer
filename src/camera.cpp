#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspectRatio, glm::vec3 camPos, float fov, float nearPlane, float farPlane)
    : aspectRatio(aspectRatio), position(camPos), fov(fov), nearPlane(nearPlane), farPlane(farPlane) {
    calculateViewProjection();
}

void Camera::move(glm::vec3 localDir, float dt) {
    
    if(glm::dot(localDir, localDir) == 0.0f) return;

    glm::vec3 front = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));

    glm::vec3 right = glm::normalize(glm::cross(front, {0.0f, 1.0f, 0.0f}));
    glm::vec3 up  = glm::normalize(glm::cross(right, front));

    localDir = glm::normalize(localDir);
    position += (right * localDir.x + up * localDir.y + front * localDir.z) * speed * dt;
    dirty = true;
}

void Camera::setPosition(glm::vec3 p) {
    position = p;
    dirty = true;
}

void Camera::setRotation(float yaw, float pitch) {
    this->pitch = pitch;
    this->yaw = yaw;
    dirty = true;
}

void Camera::setFov(float degrees) {
    fov = degrees;
    dirty = true;
}

void Camera::setClipPlanes(float nearPlane, float farPlane) {
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    dirty = true;
}

void Camera::setAspectRatio(float ratio) {
    aspectRatio = ratio;
    dirty = true;
}

void Camera::setSpeed(float s) {
    if(s < 0) return;
    speed = s;
}

const glm::mat4& Camera::getView() const {
    if(dirty) {
        calculateViewProjection();
        dirty = false;
    }

    return view;
}

const glm::mat4& Camera::getProjection() const {
    if(dirty) {
        calculateViewProjection();
        dirty = false;
    }

    return projection;
}

const glm::mat4& Camera::getViewProjection() const {
    if(dirty) {
        calculateViewProjection();
        dirty = false;
    }

    return viewProjection;
}

void Camera::calculateViewProjection() const {
    glm::vec3 front = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));

    glm::vec3 right = glm::normalize(glm::cross(front, {0.0f, 1.0f, 0.0f}));
    glm::vec3 up  = glm::normalize(glm::cross(right, front));

    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

    viewProjection = projection * view;

}