#include "yepch.h"
#include "CameraController.h"

namespace YSJEN {
    void CameraController::OnUpdate(Timestep ts)
    {
        if (!m_Camera) return;  // 安全检查
        
        glm::vec3 currentPos = m_Camera->GetPosition();
        float currentRotation = m_Camera->GetRotation();  

        if (Input::IsKeyPressed(YE_KEY_W))
            currentPos.y += m_MoveSpeed*ts;  
        else if (Input::IsKeyPressed(YE_KEY_S))
            currentPos.y -= m_MoveSpeed * ts;
        if (Input::IsKeyPressed(YE_KEY_A))
            currentPos.x -= m_MoveSpeed * ts;
        else if (Input::IsKeyPressed(YE_KEY_D))
            currentPos.x += m_MoveSpeed * ts;
        if (Input::IsKeyPressed(YE_KEY_Q))
            currentPos.z += m_MoveSpeed * ts;
        else if (Input::IsKeyPressed(YE_KEY_E))
            currentPos.z -= m_MoveSpeed * ts;

        if (Input::IsKeyPressed(YE_KEY_LEFT))
            currentRotation -= m_RotationSpeed * ts;
        else if (Input::IsKeyPressed(YE_KEY_RIGHT))
            currentRotation += m_RotationSpeed * ts;

        m_Camera->SetPosition(currentPos);
        m_Camera->SetRotation(currentRotation);
    }
}