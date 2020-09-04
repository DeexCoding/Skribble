#pragma once

#include "Skribble/Render/VertexBuffer.h"

namespace Skribble
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* vertices, uint32_t size);
		virtual ~GLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return layout; }
		virtual void SetLayout(const BufferLayout _layout) override { layout = _layout; }

	private:
		uint32_t rendererID;
		BufferLayout layout;

	};
}