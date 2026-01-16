#pragma once
#include "YSJEN/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;
namespace YSJEN {
	class OpenGLShader:public Shader{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind()const override;
		virtual void Unibind()const override;

		virtual const std::string& GetName() const override { return m_Name; };
		
		void UpUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UpUniformMat4(const std::string& name, const glm::mat4& matrix) const;
		void UpUniformInt(const std::string& name, int value) const;
		void UpUniformFloat1(const std::string& name, float value) const;
		void UpUniformFloat2(const std::string& name, const glm::vec2& value) const;
		void UpUniformFloat3(const std::string& name, const glm::vec3& value) const;
		void UpUniformFloat4(const std::string& name, const glm::vec4& value) const;
	private:
		std::string ReadFlie(const std::string& filepath);
		std::unordered_map<GLenum,std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}