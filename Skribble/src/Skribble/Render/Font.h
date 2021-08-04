#pragma once

#include <string>
#include <map>

#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

namespace Skribble
{
	struct Character
	{
		Ref<Texture2D> texture;
		glm::ivec2 size;
		glm::ivec2 bearing; //Distance from texture origin to top left of character
		glm::ivec2 advance; //Distance from origin to next character's origin
	};

	class Font
	{
	public:
		Font(int height);
		~Font();

		static Ref<Font> Create(int height);

		void Load(const std::string& fliepath);
		Character GetCharacter(char c) { return characters[c]; }

	private:
		int height;
		std::map<char, Character> characters;
	};
}