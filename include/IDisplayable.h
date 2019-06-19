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
    struct IDisplay;
    struct IDisplayable
    {
        virtual ~IDisplayable(){}

        /**
         * @brief 
         * 
         * @param display A display interface to display on
        */
        virtual void display(std::shared_ptr<IDisplay> display) const = 0;
    };
}

#endif