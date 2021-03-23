#include "skpch.h"

#include "GLTexture.h"

#include "stb_image.h"

namespace Skribble
{
	GLTexture2D::GLTexture2D(uint32_t width, uint32_t height) : width(width), height(height)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, this->width, this->height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);

	}

	GLTexture2D::GLTexture2D(const std::string& path) : path(path)
	{
		int width, height, channels;
		
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		SKRIBBLE_ASSERT(data, "Failed to load image!");

		this->width = width;
		this->height = height;

		GLenum glFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			glFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			glFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		SKRIBBLE_CORE_ASSERT(glFormat & dataFormat, "Format not supported");

		internalFormat = glFormat;
		dataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, glFormat, this->width, this->height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTextureSubImage2D(rendererID, 0, 0, 0, this->width, this->height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void GLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = dataFormat == GL_RGBA ? 4 : 3;
		SKRIBBLE_CORE_ASSERT(size == width * height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void GLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererID);
	}

	void GLTexture2D::Unbind(uint32_t slot) const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}