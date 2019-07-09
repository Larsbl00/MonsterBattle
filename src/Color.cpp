/**
 * @file Color.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-09
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Color.h"

namespace monsterbattle
{
    namespace colors 
    {
        Color::Color(uint8_t red, uint8_t green, uint8_t blue):
            red(red), green(green), blue(blue), alpha(255)
        {}

        Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha):
            red(red), green(green), blue(blue), alpha(alpha)
        {}

        uint8_t Color::to8BitColor() const
        {
            return 
            (this->red * COLOR_8_BIT_CHANNEL_MAX / COLOR_RGB_CHANNEL_MAX) << 5
            | (this->green * COLOR_8_BIT_CHANNEL_MAX / COLOR_RGB_CHANNEL_MAX) << 2
            | (this->blue * COLOR_8_BIT_CHANNEL_MAX / COLOR_RGB_CHANNEL_MAX);
        }
    }
}