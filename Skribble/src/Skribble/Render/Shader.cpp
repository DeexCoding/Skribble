#include "skpch.h"

#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/GLShader.h"

namespace Skribble
{
	Ref<Shader> Shader::Create(const std::string& fliepath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPIType::None:
			return nullptr;

		case RenderAPIType::OpenGL:
			return CreateRef<GLShader>(fliepath);
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPIType::None:
			return nullptr;

		case RenderAPIType::OpenGL:
			return CreateRef<GLShader>(name, vertexSrc, fragmentSrc);
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");

		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		SKRIBBLE_CORE_ASSERT(shaders.find(name) == shaders.end(), "Shader already exists!");
		shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		SKRIBBLE_CORE_ASSERT(Exists(name), "Shader doesn't exist!");
		return shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name)
	{
		return ShaderLibrary::shaders.find(name) != shaders.end();
	}
}