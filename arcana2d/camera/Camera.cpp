#include "camera/Camera.hpp"
#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace arcana {
    // CAMERA IMPL.
    Camera::Camera() {
        dimensions = Vector2(0,0);
        offset = Vector2(0,0);
        zoom = 1.0f;
        rotation = 0.0f;
    }

    Camera::~Camera() {

    }

    Mat4 Camera::getProjectionMatrix() {
        // First create the projection matrix
        Mat4 projectionMat = glm::ortho(0.0f, dimensions.x, dimensions.y, 0.0f, -100.0f, 100.0f);
        projectionMat = glm::translate(projectionMat, Vector3(-offset, 0.0f));
        projectionMat = glm::translate(projectionMat, Vector3(dimensions.x/2, dimensions.y/2, 0.0f));
        projectionMat = glm::rotate(projectionMat, glm::radians(rotation), Vector3(0.0f, 0.0f, 1.0f));
        projectionMat = glm::scale(projectionMat, Vector3(zoom, zoom, 1.0f));
        projectionMat = glm::translate(projectionMat, Vector3(-dimensions.x/2, -dimensions.y/2, 0.0f));
        return projectionMat;
    }
}