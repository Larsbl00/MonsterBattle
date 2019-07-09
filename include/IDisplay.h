/**
 * @file IDisplay.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef IDISPLAY_H
#define IDISPLAY_H

#include <memory>

#include "IDisplayable.h"
#include "Color.h"
#include "Vector.h"

namespace monsterbattle
{
    struct IDisplayable; //Forward deeclaration so we can use it

    struct IDisplay
    {
        virtual ~IDisplay(){}

        virtual void clear() = 0;
        virtual void display() = 0;
        virtual const Vector2i32& getSize() const = 0;
        virtual void setPixel(const Vector2i32& pixel, char value) = 0;
        virtual void setPixel(const Vector2i32& pixel, const monsterbattle::colors::Color& color) = 0;
        virtual void setPixel(const Vector2i32& pixel, char value, const monsterbattle::colors::Color& color) = 0;
    };
    
}

#endif