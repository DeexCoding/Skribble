#include "skpch.h"
#include "GLShader.h"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace Skribble
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}

		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}

		SKRIBBLE_CORE_ASSERT(0, "Unknown shader type!")

		return 0;
	}

	GLShader::GLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

		auto lastDot = filepath.rfind('.');

		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

		name = filepath.substr(lastSlash, count);
	}

	GLShader::GLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: name(name)
	{
		std::unordered_map<GLenum, std::string> srcs;
		srcs[GL_VERTEX_SHADER] = vertexSrc;
		srcs[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(srcs);
	}

	GLShader::~GLShader()
	{
		glDeleteProgram(rendererID);
	}

	void GLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs)
	{
		GLuint program = glCreateProgram();

		SKRIBBLE_CORE_ASSERT(shaderSrcs.size() <= 5, "More than 5 shaders aren't supported!");

		std::array<GLenum, 5> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto& kv : shaderSrcs)
		{
			GLenum type = kv.first;
			const std::string& src = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* srcCStr = (const GLchar*)src.c_str();
			glShaderSource(shader, 1, &srcCStr, 0);

			glCompileShader(shader);

			GLint shaderCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

			if (shaderCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				SKRIBBLE_CORE_ERROR("{0} shader compilation failed!", type);
				SKRIBBLE_CORE_ERROR("{0}", infoLog.data());
				SKRIBBLE_CORE_ASSERT(false, "{0} shader compilation failed!", type);

				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLuint linkedProgram = 0;

		glGetProgramiv(program, GL_LINK_STATUS, (int*)&linkedProgram);

		if (linkedProgram == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}
			
			SKRIBBLE_CORE_ERROR("Shader link failed!");
			SKRIBBLE_CORE_ERROR("{0}", infoLog.data());
			SKRIBBLE_CORE_ASSERT(false, "Shader link failed!");

			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}
		
		rendererID = program;
	}

	std::unordered_map<GLenum, std::string> GLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";

		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);

			SKRIBBLE_CORE_ASSERT(eol != std::string::npos, "Syntax error!");

			//TODO: doesn't matter how may speces there are after #type
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			SKRIBBLE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, 
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	std::string GLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream stream(filepath, std::ios::in | std::ios::binary);

		if (stream)
		{
			stream.seekg(0, std::ios::end);
			result.resize(stream.tellg());
			stream.seekg(0, std::ios::beg);
			stream.read(&result[0], result.size());
			stream.close();
		}
		else
		{
			SKRIBBLE_CORE_ERROR("Couldn't open file '{0}'", filepath);
		}

		return result;
	}

	void GLShader::Bind() const
	{
		glUseProgram(rendererID);
	}

	void GLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void GLShader::SetInt(const std::string& name, const int& value)
	{
		UploadUniformInt(name, value);
	}

	void GLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void GLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void GLShader::SetFloat2(const std::string& name, const glm::vec2& values)
	{
		UploadUniformFloat2(name, values);
	}

	void GLShader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		UploadUniformFloat3(name, values);
	}

	void GLShader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		UploadUniformFloat4(name, values);
	}

	void GLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		UploadUniformMat3(name, matrix);
	}

	void GLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		UploadUniformMat4(name, matrix);
	}

	void GLShader::UploadUniformInt(const std::string& name, const int& value)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1i(location, value);
	}

	void GLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void GLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, value);
	}

	void GLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void GLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void GLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void GLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void GLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}