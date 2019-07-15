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

#include <iostream>
#include <cstdint>
#include <cstring>

#define COLOR_8_BIT_CHANNEL_MAX (7)
#define COLOR_16_BIT_CHANNEL_MAX (15)
#define COLOR_RGB_CHANNEL_MAX (255)

namespace monsterbattle
{
    struct Color
    {
        const static Color Red;
        const static Color Green;
        const static Color Blue;

        const static Color Yellow;
        const static Color Cyan;
        const static Color Magenta;

        const static Color Black;
        const static Color White;

        Color() = default;
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

        void operator=(const Color& other);
        void operator=(Color&& other);

        friend std::ostream& operator<<(std::ostream& stream, const Color& color);
        friend bool operator== (const Color& c0, const Color& c1);
        friend bool operator!= (const Color& c0, const Color& c1);
    };
}

#endif