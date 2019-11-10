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
        virtual ~IMoveable() noexcept = default;
        /**
         * @brief Moves the object with a given delta
         * 
         * @param direction Direction to move from root
        */
        virtual void move(const Vector2i32& direction) = 0;

        /**
         * @brief Moves the object to a given location
         * 
         * @param location 
        */
        virtual void moveTo(const Vector2i32& location) = 0;
    };
}


#endif