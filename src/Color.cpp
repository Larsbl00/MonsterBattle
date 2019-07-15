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

#define COLOR_DEFINE(COLOR_NAME, RED, GREEN, BLUE) (const Color Color:: COLOR_NAME (RED,GREEN,BLUE))

namespace monsterbattle
{
    const Color Color::Red(255,0,0);
    const Color Color::Green(0,255,0);
    const Color Color::Blue(0,0,255);

    const Color Color::Yellow(255,255,0);
    const Color Color::Cyan(0,255,255);
    const Color Color::Magenta(255,0,255);

    const Color Color::Black(0,0,0,0);
    const Color Color::White(255,255,255,255);

    Color::Color(uint8_t red, uint8_t green, uint8_t blue):
        red(red), green(green), blue(blue), alpha(255)
    {}

    Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha):
        red(red), green(green), blue(blue), alpha(alpha)
    {}

    uint8_t Color::to8BitColor() const
    {
        return 0
        | (((this->red * 7 / COLOR_RGB_CHANNEL_MAX) << 5))
        | (((this->green * 7 / COLOR_RGB_CHANNEL_MAX) << 2))
        | (((this->blue * 7 / COLOR_RGB_CHANNEL_MAX)));
    }

    void Color::operator=(const Color& other)
    {
        memcpy(this, &other, sizeof(other));
    }

    void Color::operator=(Color&& other)
    {
        *this = other;
    }

    /***********************************
     * 
     * Friends
     * 
     */
    std::ostream& operator<<(std::ostream& stream, const Color& color)
    {
        return stream << '{' << (int)color.red << ',' << (int)color.green << ',' << (int)color.blue << ',' << (int)color.alpha << '}';
    }   

    bool operator== (const Color& c0, const Color& c1)
    {
        return 
            c0.red == c1.red &&
            c0.blue == c1.blue &&
            c0.green == c1.green;
    }

    bool operator!= (const Color& c0, const Color& c1)
    {
        return !(c0 == c1);
    }
}