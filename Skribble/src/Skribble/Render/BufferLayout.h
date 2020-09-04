#pragma once

#include <cstdint>

namespace Skribble
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
	};

	static uint32_t GetShaderDataTypeSize(ShaderDataType _type)
	{
		switch (_type)
		{

		//A float is 4 bytes
		case Skribble::ShaderDataType::Float:
			return 4;
		case Skribble::ShaderDataType::Float2:
			return 8;
		case Skribble::ShaderDataType::Float3:
			return 12;
		case Skribble::ShaderDataType::Float4:
			return 16;

		//An int is 4 bytes
		case Skribble::ShaderDataType::Int:
			return 4;
		case Skribble::ShaderDataType::Int2:
			return 8;
		case Skribble::ShaderDataType::Int3:
			return 12;
		case Skribble::ShaderDataType::Int4:
			return 16;

		//A matrix is made up of floats
		case Skribble::ShaderDataType::Mat3:
			return 36;
		case Skribble::ShaderDataType::Mat4:
			return 64;
		case Skribble::ShaderDataType::Bool:
			return 1;
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t offset;
		uint32_t size;
		bool normalized;

		BufferElement() {}

		BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized = false) : name(_name), type(_type),
			size(GetShaderDataTypeSize(_type)), offset(0), normalized(_normalized) { }

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case Skribble::ShaderDataType::Float:
				return 1;
			case Skribble::ShaderDataType::Float2:
				return 2;
			case Skribble::ShaderDataType::Float3:
				return 3;
			case Skribble::ShaderDataType::Float4:
				return 4;
			case Skribble::ShaderDataType::Int:
				return 1;
			case Skribble::ShaderDataType::Int2:
				return 2;
			case Skribble::ShaderDataType::Int3:
				return 3;
			case Skribble::ShaderDataType::Int4:
				return 4;
			case Skribble::ShaderDataType::Mat3:
				return 9;
			case Skribble::ShaderDataType::Mat4:
				return 16;
			case Skribble::ShaderDataType::Bool:
				return 1;
			}

			SKRIBBLE_CORE_ASSERT(false, "Unknown shader data type!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement> _elements) : elements(_elements) 
		{
			uint32_t offset = 0;
			stride = 0;

			for (auto& _element : elements)
			{
				_element.offset = offset;
				offset += _element.size;
				stride += _element.size;
			}
		}

		inline const std::vector<BufferElement>& GetElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

		inline uint32_t GetStride() const { return stride; }

	private:
		std::vector<BufferElement> elements;
		uint32_t stride;
	};
}