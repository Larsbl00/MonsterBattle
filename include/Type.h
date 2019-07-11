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
#include <iostream>

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


    std::ostream& operator<<(std::ostream& str, Type type);
    std::istream& operator>>(std::istream& str, Type& type);
}

#endif
