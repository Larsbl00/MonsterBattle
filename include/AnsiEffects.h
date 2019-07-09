/**
 * @file AnsiEffects.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-09
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef ANSI_EFFECTS_H
#define ANSI_EFFECTS_H

#include <ostream>

namespace monsterbattle
{
    namespace text
    {
        enum class AnsiTextEffect : unsigned short
        {
            EFFECT_NORMAL = 0,
            EFFECT_BOLD = 1,
            EFFECT_ITALIC = 2,
            EFFECT_UNDERLINE = 3,
            EFFECT_BLINK_SLOW = 4,
            EFFECT_BLINK_FAST = 5,
            EFFECT_SWAP_BACKGROUND_FOREGROUND = 6,
            EFFECT_STRIKE_THROUGH = 7, 
            EFFECT_SET_FOREGROUND = 38, //Use a 5;n or 2;r;g;b for 8 and 24 bit colloring
            EFFECT_SET_BACKGROUND = 48, //Use a 5;n or 2;r;g;b for 8 and 24 bit colloring
        };

        std::ostream& operator<<(std::ostream& str, const AnsiTextEffect& effect);
    }
}

#endif