#include "skpch.h"

#include "GLTexture.h"

#include "stb_image.h"

namespace Skribble
{
	bool byteAlignmentRestricted = true;

	int FormatToBPP(GLenum internalFormat)
	{
		switch (internalFormat)
		{
		case GL_RGBA2:
			return 4;

		case GL_RGBA4:
			return 4;

		case GL_RGBA8:
			return 4;

		case GL_RGBA16:
			return 4;

		case GL_RGB4:
			return 3;

		case GL_RGB5:
			return 3;

		case GL_RGB8:
			return 3;

		case GL_RGB12:
			return 3;

		case GL_RGB16:
			return 3;

		case GL_RG8:
			return 2;

		case GL_RG16:
			return 2;

		case GL_RED:
			return 1;

		case GL_R8:
			return 1;

		case GL_R16:
			return 1;

		default:
			break;
		}

		SKRIBBLE_CORE_ERROR("Internal format not supported!");
		return 0;
	}

	GLTexture2D::GLTexture2D(uint32_t width, uint32_t height, int channels, int channelSize) : 
		width(width), height(height)
	{
		SetFormats(channels, channelSize);

		SKRIBBLE_CORE_ASSERT(dataFormat & internalFormat, "Format not supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, width, height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}


	GLTexture2D::GLTexture2D(const std::string& path) : path(path)
	{
		int width, height, channels;
		
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		SKRIBBLE_ASSERT(data, "Failed to load image!");

		this->width = width;
		this->height = height;

		SetFormats(channels, 8);

		SKRIBBLE_CORE_ASSERT(dataFormat & internalFormat, "Format not supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, this->width, this->height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureSubImage2D(rendererID, 0, 0, 0, this->width, this->height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void GLTexture2D::SetFormats(int channels, int channelSize)
	{
		internalFormat = 0;
		dataFormat = 0;

		if (channels == 4)
		{
			if (channelSize == 2)
			{
				internalFormat = GL_RGBA2;
			}
			else if (channelSize == 4)
			{
				internalFormat = GL_RGBA4;
			}
			else if (channelSize == 8)
			{
				internalFormat = GL_RGBA8;
			}
			else if (channelSize == 12)
			{
				internalFormat = GL_RGBA12;
			}
			else if (channelSize == 16)
			{
				internalFormat = GL_RGBA16;
			}

			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			if (channelSize == 5)
			{
				internalFormat = GL_RGB5;
			}
			else if (channelSize == 4)
			{
				internalFormat = GL_RGB4;
			}
			else if (channelSize == 8)
			{
				internalFormat = GL_RGB8;
			}
			else if (channelSize == 12)
			{
				internalFormat = GL_RGB12;
			}
			else if (channelSize == 16)
			{
				internalFormat = GL_RGB16;
			}

			dataFormat = GL_RGB;
		}
		else if (channels == 2)
		{
			if (channelSize == 8)
			{
				internalFormat = GL_RG8;
			}
			else if (channelSize == 16)
			{
				internalFormat = GL_RG16;
			}

			dataFormat = GL_RG;
		}
		else if (channels == 1)
		{
			if (channelSize == 1)
			{
				internalFormat = GL_RED;
			}
			else if (channelSize == 8)
			{
				internalFormat = GL_R8;
			}
			else if (channelSize == 16)
			{
				internalFormat = GL_R16;
			}

			dataFormat = GL_RED;
		}
		else
		{
			SKRIBBLE_CORE_ERROR("Channel count not suported!");
		}
		
		SKRIBBLE_CORE_ASSERT(dataFormat > 0, "Channel count not supported!");
		SKRIBBLE_CORE_ASSERT(internalFormat > 0, "Channel size not supported!");
	}

	void GLTexture2D::SetData(void* data, uint32_t size)
	{
		//bpp - Bytes per pixel
		uint32_t bytesPerPixel = FormatToBPP(internalFormat);
		SKRIBBLE_CORE_ASSERT(size == width * height * bytesPerPixel, "Data must be entire texture!");
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