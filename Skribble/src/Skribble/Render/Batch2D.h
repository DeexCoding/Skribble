#pragma once

#include "Camera.h"
#include "Texture.h"

namespace Skribble
{
	class Batch2D
	{
	public:
		static void Initalize();
		static void Shutdown();

		static void Begin(const Camera& camera);
		static void End();

		static void Flush();

		static void DrawQuad(const glm::vec2& position, float sortingLayer, float rotation, const glm::vec2& size,
			const glm::vec4& color, const Ref<Texture2D> texture, float tilingFactor);

	private:
		static void NewBatch();
	};
}