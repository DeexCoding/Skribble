#include "skpch.h"

#include "Shader.h"

#include <glad/glad.h>

namespace Skribble
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint shaderCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompiled);

		if (shaderCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			SKRIBBLE_CORE_ERROR("Vertex shader compilation failed!");
			SKRIBBLE_CORE_ERROR("{0}", infoLog.data());
			SKRIBBLE_CORE_ASSERT(false, "Vertex shader compilation failed!");

			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCompiled);

		if (shaderCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			glDeleteShader(fragmentShader);

			SKRIBBLE_CORE_ERROR("Fragment shader compilation failed!");
			SKRIBBLE_CORE_ERROR("{0}", infoLog.data());
			SKRIBBLE_CORE_ASSERT(false, "Fragment shader compilation failed!");

			return;
		}

		rendererID = glCreateProgram();

		glAttachShader(rendererID, vertexShader);
		glAttachShader(rendererID, fragmentShader);

		glLinkProgram(rendererID);

		GLuint linkedProgram = 0;

		glGetProgramiv(rendererID, GL_LINK_STATUS, (int *)&linkedProgram);

		if (linkedProgram == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(rendererID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			SKRIBBLE_CORE_ERROR("Shader link failed!");
			SKRIBBLE_CORE_ERROR("{0}", infoLog.data());
			SKRIBBLE_CORE_ASSERT(false, "Shader link failed!");

			return;
		}

		glDetachShader(rendererID, vertexShader);
		glDetachShader(rendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(rendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(rendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}