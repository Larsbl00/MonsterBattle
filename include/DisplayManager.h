/**
 * @file DisplayManager.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <algorithm>
#include <memory>
#include <vector>
#include <exception>

#include "IDisplay.h"
#include "IDisplayable.h"

namespace monsterbattle 
{
    class DisplayManager
    {
        public: 
        ~DisplayManager() noexcept = default;
        DisplayManager(const DisplayManager&) = delete;

        static DisplayManager& getInstance();

        /**
         * @brief Adds an item to the render queue
         * 
         * @param item A pointer to an item that needs to be displayed, keep the item alive while it remains in the queue
        */
        void addToRenderQueue(IDisplayable* item);
        void displayAllItems();
        /**
         * @brief 
         * 
         * @param item 
        */
        void removeFromRenderQueue(IDisplayable* item);

        /**
         * @brief Set the Display object
         * 
         * @param display A pointer to the new display, keep the item alive as long as you're using it
        */
        void setDisplay(IDisplay* display);

        private:
        IDisplay* display;
        std::vector<IDisplayable*> items;

        DisplayManager();
    };  
}

#endif