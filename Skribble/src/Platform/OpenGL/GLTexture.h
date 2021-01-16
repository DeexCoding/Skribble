#pragma once

#include "Skribble/Render/Texture.h"

namespace Skribble
{
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(const std::string& path);
		virtual ~GLTexture2D();

		virtual uint32_t GetWidth() const override { return width; }
		virtual uint32_t GetHeight() const override { return height; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		std::string path;
		uint32_t width, height;
		uint32_t rendererID;

	};
}