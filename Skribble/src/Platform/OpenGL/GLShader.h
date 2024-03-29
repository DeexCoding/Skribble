#pragma once

#include "Skribble/Render/Shader.h"

#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Skribble
{
	class GLShader : public Shader
	{
	public:
		GLShader(const std::string& filepath);
		GLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~GLShader();

		void Bind() const override;
		void Unbind() const override;

		virtual const std::string GetName() const override { return name; }

		virtual void SetInt(const std::string& name, const int& value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		void UploadUniformInt(const std::string& name, const int& value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		std::string ReadFile(const std::string& filepath);

		uint32_t rendererID;

		std::string name;
	};

}