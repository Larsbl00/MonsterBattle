/**
 * @file ColorManager.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-09
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

#define COLOR_8_BIT_CHANNEL_MAX (7)
#define COLOR_16_BIT_CHANNEL_MAX (15)
#define COLOR_RGB_CHANNEL_MAX (255)

namespace monsterbattle
{
    namespace colors
    {
        struct Color
        {
            Color(uint8_t red, uint8_t green, uint8_t blue);
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
            Color(const Color& other) = default;
            Color(Color&& other) = default;
            ~Color() noexcept = default;
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            uint8_t alpha;

            uint8_t to8BitColor() const;
        };

        const static Color Red(255,0,0);
        const static Color Green(0,255,0);
        const static Color Blue(0,0,255);

        const static Color Orange(255,255,0);
        const static Color Cyan(0, 255,255);
        const static Color Magenta(255,0,255);

        const static Color Black(0,0,0);
        const static Color White(255,255,255,255);
    }
}

#endif