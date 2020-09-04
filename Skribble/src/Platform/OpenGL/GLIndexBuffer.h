#pragma once

#include "Skribble/Render/IndexBuffer.h"

namespace Skribble
{
	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(uint32_t* vertices, uint32_t _count);
		virtual ~GLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return count; }

	private:
		uint32_t rendererID;
		uint32_t count;

	};
}