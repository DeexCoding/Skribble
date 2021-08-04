#pragma once

#include <cstdint>
#include "Skribble/Render/Texture.h"

#include <glad/glad.h>

namespace Skribble
{
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(uint32_t width, uint32_t height, int channels, int channelSize);
		GLTexture2D(const std::string& path);
		virtual ~GLTexture2D();

		virtual uint32_t GetWidth() const override { return width; }
		virtual uint32_t GetHeight() const override { return height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void Unbind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override 
		{ 
			return rendererID == ((GLTexture2D&)other).rendererID;
		}

	private:
		void SetFormats(int channels, int channelSize);

		std::string path;
		uint32_t width, height;
		uint32_t rendererID;
		GLenum dataFormat, internalFormat;
	};
}