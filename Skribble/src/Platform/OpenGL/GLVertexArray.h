#pragma once

#include "Skribble/Render/VertexArray.h"

namespace Skribble
{
	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		virtual ~GLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& _buffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& _buffer) override;

		virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const { return vertexBuffers; }
		virtual const Ref<IndexBuffer> GetIndexBuffer() const { return indexBuffer; }

	private:
		uint32_t rendererID;
		std::vector<Ref<VertexBuffer>> vertexBuffers;
		Ref<IndexBuffer> indexBuffer;

	};
}