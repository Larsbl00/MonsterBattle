/**
 * @file IMoveable.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-23
 * 
 * @copyright Copyright (c) 2019
 * 
*/
#ifndef IMOVEABLE_H
#define IMOVEABLE_H

#include "Vector.h"

namespace monsterbattle
{
    struct IMoveable
    {
        virtual ~IMoveable() = default;
        void move(const Vector2i32& direction);
    };
}


#endif