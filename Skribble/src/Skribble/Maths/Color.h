#pragma once

#include <glm/glm.hpp>
#include <math.h>

namespace Skribble
{
    static const glm::vec4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
    static const glm::vec4 Grey = { 0.5f, 0.5f, 0.5f, 1.0f };
    static const glm::vec4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const glm::vec4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
    static const glm::vec4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
    static const glm::vec4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
    static const glm::vec4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
    static const glm::vec4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
    static const glm::vec4 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };

    static glm::vec4 HSVAtoRGBA(const glm::vec4& hsva) 
    {
        if (hsva.x > 360 || hsva.x < 0 || hsva.y > 100 || hsva.y < 0 || hsva.z > 100 || hsva.z < 0) 
        {
            return White;
        }

        float s = hsva.y / 100;
        float v = hsva.z / 100;
        float C = s * v;
        float X = C * (float)(1.0 - glm::abs(std::fmod((double)hsva.x / 60.0, 2.0) - 1.0));
        float m = v - C;
        float r, g, b;

        if (hsva.x >= 0 && hsva.x < 60)
        {
            r = C, g = X, b = 0;
        }
        else if (hsva.x >= 60 && hsva.x < 120)
        {
            r = X, g = C, b = 0;
        }
        else if (hsva.x >= 120 && hsva.x < 180)
        {
            r = 0, g = C, b = X;
        }
        else if (hsva.x >= 180 && hsva.x < 240)
        {
            r = 0, g = X, b = C;
        }
        else if (hsva.x >= 240 && hsva.x < 300)
        {
            r = X, g = 0, b = C;
        }
        else 
        {
            r = C, g = 0, b = X;
        }

        float R = (r + m);
        float G = (g + m);
        float B = (b + m);

        return { R, G, B, hsva.a };
    }

    static glm::vec4 RGBAtoHSVA(const glm::vec4& rgba)
    {
        glm::vec4 hsva;
        float min, max, delta;

        min = rgba.r < rgba.g ? rgba.r : rgba.g;
        min = min < rgba.b ? min : rgba.b;

        max = rgba.r > rgba.g ? rgba.r : rgba.g;
        max = max > rgba.b ? max : rgba.b;

        hsva.z = max;

        delta = max - min;

        if (delta < 0.00001f)
        {
            hsva.y = 0;
            hsva.x = 0;

            return hsva;
        }
        if (max > 0.0f) 
        { // NOTE: if Max is == 0, this divide would cause a crash
            hsva.y = (delta / max);
        }
        else 
        {
            hsva.y = 0.0f;
            hsva.x = NAN;
            return hsva;
        }

        if (rgba.r >= max)
        {
            hsva.x = (rgba.g - rgba.b) / delta;
        }
        else
        {
            if (rgba.g >= max)
            {
                hsva.x = 2.0f + (rgba.b - rgba.r) / delta;
            }
            else
            {
                hsva.x = 4.0f + (rgba.r - rgba.g) / delta;
            }
        }

        hsva.x *= 60.0f;

        if (hsva.x < 0.0f)
        {
            hsva.x += 360.0f;
        }

        return hsva;
    }
}