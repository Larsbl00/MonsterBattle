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
#include "Vector.h"

namespace monsterbattle
{
    struct IDisplayable; //Forward deeclaration so we can use it

    struct IDisplay
    {
        virtual ~IDisplay(){}
        /**
         * @brief Adds an item to an internal queue
         * 
         * @param item 
        */
        virtual void addToDisplayQueue(const std::shared_ptr<IDisplayable*> item) = 0;

        virtual const Vector2i32& getSize() const;
        virtual void setPixel(const Vector2i32& pixel, char value);
    };
    
}

#endif