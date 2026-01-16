#pragma once
#include "YSJEN/Renderer/Camera.h"
#include "YSJEN/Input.h"
#include "YSJEN/KeyCodes.h"
#include "YSJEN/Core/Timestep.h"

namespace YSJEN {
    class CameraController {
    public:
        CameraController() : m_Camera(nullptr), m_MoveSpeed(1.0f), m_RotationSpeed(10.0f) {}
        CameraController(Ref<Camera> camera)
            : m_Camera(camera.get()), m_MoveSpeed(1.0f), m_RotationSpeed(10.0f) {}

        void setCamera(Camera* camera) {
            m_Camera = camera;
            m_MoveSpeed = 1.0f;
            m_RotationSpeed = 10.0f;
        }

        void OnUpdate(Timestep ts);  

        void SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
        void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }

    private:
        Camera* m_Camera;  // 不拥有所有权，只持有引用
        float m_MoveSpeed;
        float m_RotationSpeed;
    };
}