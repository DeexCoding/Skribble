#type vertex
#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexIndex;
layout(location = 4) in float aTilingFactor;
layout(location = 5) in int aFlipX;
layout(location = 6) in int aFlipY;

uniform mat4 uViewProjection;

out vec4 vColor;
out vec2 vTexCoord;
out flat float vTexIndex;
out float vTilingFactor;

void main()
{
	vTexCoord = aTexCoord;

	if (aFlipX != 0)
	{
		vTexCoord.x *= -1.0;
		vTexCoord.x += 1.0;
	}
	if (aFlipY != 0)
	{
		vTexCoord.y *= -1.0;
		vTexCoord.y += 1.0;
	}

	vColor = aColor;
	vTexIndex = aTexIndex;
	vTilingFactor = aTilingFactor;
	gl_Position = uViewProjection * vec4(aPosition, 1.0);
}

#type pixel
#version 450 core

layout(location = 0) out vec4 color;

in vec4 vColor;
in vec2 vTexCoord;
in flat float vTexIndex;
in float vTilingFactor;

uniform sampler2D uTextures[32];

void main()
{
	vec4 texColor = vColor;
	switch(int(vTexIndex))
	{
		case 0: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 1: texColor *= texture(uTextures[1], vTexCoord * vTilingFactor); break;
		case 2: texColor *= texture(uTextures[2], vTexCoord * vTilingFactor); break;
		case 3: texColor *= texture(uTextures[3], vTexCoord * vTilingFactor); break;
		case 4: texColor *= texture(uTextures[4], vTexCoord * vTilingFactor); break;
		case 5: texColor *= texture(uTextures[5], vTexCoord * vTilingFactor); break;
		case 6: texColor *= texture(uTextures[6], vTexCoord * vTilingFactor); break;
		case 7: texColor *= texture(uTextures[7], vTexCoord * vTilingFactor); break;
		case 8: texColor *= texture(uTextures[8], vTexCoord * vTilingFactor); break;
		case 9: texColor *= texture(uTextures[9], vTexCoord * vTilingFactor); break;
		case 10: texColor *= texture(uTextures[10], vTexCoord * vTilingFactor); break;
		case 11: texColor *= texture(uTextures[11], vTexCoord * vTilingFactor); break;
		case 12: texColor *= texture(uTextures[12], vTexCoord * vTilingFactor); break;
		case 13: texColor *= texture(uTextures[13], vTexCoord * vTilingFactor); break;
		case 14: texColor *= texture(uTextures[14], vTexCoord * vTilingFactor); break;
		case 15: texColor *= texture(uTextures[15], vTexCoord * vTilingFactor); break;
		case 16: texColor *= texture(uTextures[16], vTexCoord * vTilingFactor); break;
		case 17: texColor *= texture(uTextures[17], vTexCoord * vTilingFactor); break;
		case 18: texColor *= texture(uTextures[18], vTexCoord * vTilingFactor); break;
		case 19: texColor *= texture(uTextures[19], vTexCoord * vTilingFactor); break;
		case 20: texColor *= texture(uTextures[20], vTexCoord * vTilingFactor); break;
		case 21: texColor *= texture(uTextures[21], vTexCoord * vTilingFactor); break;
		case 22: texColor *= texture(uTextures[22], vTexCoord * vTilingFactor); break;
		case 23: texColor *= texture(uTextures[23], vTexCoord * vTilingFactor); break;
		case 24: texColor *= texture(uTextures[24], vTexCoord * vTilingFactor); break;
		case 25: texColor *= texture(uTextures[25], vTexCoord * vTilingFactor); break;
		case 26: texColor *= texture(uTextures[26], vTexCoord * vTilingFactor); break;
		case 27: texColor *= texture(uTextures[27], vTexCoord * vTilingFactor); break;
		case 28: texColor *= texture(uTextures[28], vTexCoord * vTilingFactor); break;
		case 29: texColor *= texture(uTextures[29], vTexCoord * vTilingFactor); break;
		case 30: texColor *= texture(uTextures[30], vTexCoord * vTilingFactor); break;
		case 31: texColor *= texture(uTextures[31], vTexCoord * vTilingFactor); break;
	}

	color = vec4(vColor.r, vColor.g, vColor.b, vColor.a * texColor.r);

	if (vTexIndex == 0)
	{
		color = vec4(0.0, 0.0, 0.0, 1.0);
	}
}