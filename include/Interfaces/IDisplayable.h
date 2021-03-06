/**
 * @file IDisplayable.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include <memory.h> 

#include "IDisplay.h"

namespace monsterbattle
{
    struct IDisplay; //Forward decleration, so we can use it 
    
    struct IDisplayable
    {
        virtual ~IDisplayable() = default;

        /**
         * @brief Displays an item on a given display
         * 
         * @param display 
        */
        virtual void display(IDisplay& display) const = 0;
    };
}

#endif