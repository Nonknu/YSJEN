#include"yepch.h"
#include"Camera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace YSJEN {
    Camera::Camera(float left, float right, float bottom, float top,float nearPlane, float farPlane)
        : m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top),
        m_Near(-1.0f), m_Far(1.0f),
        m_IsOrthographic(true),
        position(0.0f, 0.0f, 0.0f),
        forward(0.0f, 0.0f, -1.0f),
        up(0.0f, 1.0f, 0.0f)
    {
        m_IsOrthographic = true;

        projectionMatrix = glm::ortho(left, right, bottom, top, m_Near, m_Far);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)*
            glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0,0,1));

        viewMatrix = glm::inverse(transform);

        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
        : m_FOV(fov), m_AspectRatio(aspectRatio), m_Near(nearPlane), m_Far(farPlane),
        m_IsOrthographic(false),
        position(0.0f, 0.0f, 0.0f),
        forward(0.0f, 0.0f, -1.0f),
        up(0.0f, 1.0f, 0.0f)
    {
        m_IsOrthographic = false;

        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

        viewMatrix = glm::lookAt(position, position + forward, up);

        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    void Camera::SetLookAt(const glm::vec3& target)
    {

    }

    void Camera::SetLookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
    {
    }

    void Camera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        viewMatrix = glm::inverse(transform);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }


}