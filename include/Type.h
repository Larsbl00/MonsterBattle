/**
 * @file Types.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TYPE_H
#define TYPE_H

#include <cstdint>

namespace monsterbattle
{
    enum class Type: uint8_t
    {
        NONE,
        FIRE,
        WATER,
        GRASS,
        GROUND,
        FLYING,
        ICE,
        ELECTRIC
    };

}

#endif
