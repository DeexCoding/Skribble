#pragma once

#include "Camera.h"
#include "Texture.h"
#include "Shader.h"
#include "Font.h"

#ifdef SKRIBBLE_WINDOWS
#undef DrawText
#endif

namespace Skribble
{
	class Batch2D
	{
	public:
		static void Initalize();
		static void Shutdown();

		static void AddSamplers(Ref<Shader> shader);

		static void Begin(const Camera& camera, Ref<Shader> shader);
		static void End();

		static void Flush();

		static void DrawQuad(const glm::vec2& position, float sortingLayer, float rotation, const glm::vec2& size,
			const glm::vec4& color, const Ref<Texture2D> texture, float tilingFactor, bool flipX, bool flipY);

		static void DrawText(const glm::vec2& position, float sortingLayer, float rotation, const glm::vec2& size,
			const glm::vec4& color, const Ref<Font> font, std::string text);

	private:
		static void NewBatch();
	};
}