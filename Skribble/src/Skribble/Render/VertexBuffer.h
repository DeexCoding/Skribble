#pragma once
#include <cstdint>

#include "BufferLayout.h"

namespace Skribble
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};
}