/**
 * @file CharColorPair.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef CHAR_COLOR_PAIR
#define CHAR_COLOR_PAIR

#include "Color.h"

namespace monsterbattle
{
    struct CharColorPair
    {
        char character;
        monsterbattle::Color color;
    };

}

#endif
