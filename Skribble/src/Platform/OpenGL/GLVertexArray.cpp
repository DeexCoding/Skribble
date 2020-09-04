#include "skpch.h"

#include "GLVertexArray.h"

#include <glad/glad.h>

namespace Skribble
{
	static GLenum GetGlBaseType(ShaderDataType _type)
	{
		switch (_type)
		{
		case Skribble::ShaderDataType::Float:
			return GL_FLOAT;
		case Skribble::ShaderDataType::Float2:
			return GL_FLOAT;
		case Skribble::ShaderDataType::Float3:
			return GL_FLOAT;
		case Skribble::ShaderDataType::Float4:
			return GL_FLOAT;
		case Skribble::ShaderDataType::Int:
			return GL_INT;
		case Skribble::ShaderDataType::Int2:
			return GL_INT;
		case Skribble::ShaderDataType::Int3:
			return GL_INT;
		case Skribble::ShaderDataType::Int4:
			return GL_INT;
		case Skribble::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Skribble::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Skribble::ShaderDataType::Bool:
			return GL_BOOL;
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	GLVertexArray::GLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}

	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void GLVertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void GLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void GLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& _buffer)
	{
		SKRIBBLE_CORE_ASSERT(_buffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(rendererID);
		_buffer->Bind();

		uint32_t i = 0;

		for (const auto& _element : _buffer->GetLayout())
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, _element.GetComponentCount(), GetGlBaseType(_element.type),
				_element.normalized ? GL_TRUE : GL_FALSE, _buffer->GetLayout().GetStride(), 
				(const void*)_element.offset);
			i++;
		}

		vertexBuffers.push_back(_buffer);
	}

	void GLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& _buffer)
	{
		glBindVertexArray(rendererID);
		_buffer->Bind();

		indexBuffer = _buffer;
	}
}