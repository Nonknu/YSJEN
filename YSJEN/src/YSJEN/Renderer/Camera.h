#pragma once
#include"glm/glm.hpp"
namespace YSJEN {
	class Camera {
	public:

        Camera(){}
        Camera(float left, float right, float bottom, float top, float nearPlane, float farPlane);

        Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

		inline const glm::mat4& GetViewProjectionMatrix()const{ return viewProjectionMatrix; }

        void SetPosition(const glm::vec3& position) { this->position = position; RecalculateViewMatrix();}
        inline const glm::vec3& GetPosition() const { return position; }

        void SetLookAt(const glm::vec3& target);
        void SetLookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

        const glm::mat4& GetViewMatrix() const { return viewMatrix; }

        inline const glm::mat4& GetProjectionMatrix() const {return projectionMatrix; }

        inline float GetRotation() const { return m_Rotation; }

        void SetProjectionMatrix(const glm::mat4& projection) { projectionMatrix = projection; }

        void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }


        void SetOrthographicBounds(float left, float right, float bottom, float top) {
            m_Left = left;
            m_Right = right;
            m_Bottom = bottom;
            m_Top = top;
            RecalculateViewMatrix();
        }

        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        void RecalculateViewMatrix();
        void RecalculateProjectionMatrix();
        void RecalculateViewProjectionMatrix();


        inline bool IsOrthographic() const { return m_IsOrthographic; }
        inline bool IsPerspective() const { return !m_IsOrthographic; }
    private:

        glm::mat4 projectionMatrix;     
        glm::mat4 viewMatrix;             
        glm::mat4 viewProjectionMatrix;  


        glm::vec3 position = { 0.0f,0.0f, 0.0f };
        float m_Rotation = 0.0f;
        glm::vec3 forward;               
        glm::vec3 up;                    

        float m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far;


        float m_FOV;                     
        float m_AspectRatio;                    


        bool m_IsOrthographic;            
	};
}