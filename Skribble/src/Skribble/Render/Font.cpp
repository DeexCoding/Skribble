#include "skpch.h"

#include "Font.h"
#include "Batch2D.h"

#include <glad/glad.h>

namespace Skribble
{
	uint32_t fontCount = 0;
	FT_Library library;

	Font::Font(int height) : height(height)
	{
		if (fontCount == 0)
		{
			FT_Init_FreeType(&library);
		}

		fontCount++;
	}

	Font::~Font()
	{
		fontCount--;

		if (fontCount <= 0)
		{
			FT_Done_FreeType(library);
		}
	}

	Ref<Font> Font::Create(int height)
	{
		return CreateRef<Font>(height);
	}

	void Font::Load(const std::string& fliepath)
	{
		FT_Face fontFace;
		Ref<Texture2D> texture;

		if (FT_New_Face(library, fliepath.c_str(), 0, &fontFace))
		{
			SKRIBBLE_CORE_ERROR("Failed to load font!");
			return;
		}

		FT_Set_Pixel_Sizes(fontFace, height, height);

		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char i = 0; i < 128; i++)
		{
			if (FT_Load_Char(fontFace, i, FT_LOAD_RENDER))
			{
				continue;
			}

			if (fontFace->glyph->bitmap.width == 0 || fontFace->glyph->bitmap.rows == 0)
			{
				characters[i] =
				{
					nullptr,
					glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
					glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top),
					glm::ivec2(fontFace->glyph->advance.x, fontFace->glyph->advance.y)
				};

				continue;
			}

			/* convert to an anti-aliased bitmap */
			//FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL);

			/*When there will be an asset pipleine system it should be converted into a bitmap file and that 
			should be loaded into a texture*/
			Ref<Texture2D> tex = Texture2D::Create(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, 
				1, 8);
			
			tex->Bind();
			tex->SetData(fontFace->glyph->bitmap.buffer, 
				fontFace->glyph->bitmap.width * fontFace->glyph->bitmap.rows);

			characters[i] =
			{
				tex,
				glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
				glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top),
				glm::ivec2(fontFace->glyph->advance.x, fontFace->glyph->advance.y)
			};
		}

		FT_Done_Face(fontFace);
	}
}