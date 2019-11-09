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
#include "Singleton.h"

namespace monsterbattle 
{
    class DisplayManager:
        public Singleton<DisplayManager>
    {
        //Declare friend to access private constructor
        friend Singleton;
        
        public: 

        ~DisplayManager() noexcept = default;
        DisplayManager(const DisplayManager&) = delete;

        /**
         * @brief Adds an item to the render queue
         * 
         * @param item A pointer to an item that needs to be displayed, keep the item alive while it remains in the queue
         * 
         * @throw invalid_argument Item to add is a null pointer
        */
        void addToRenderQueue(const IDisplayable* item);

        /**
         * @brief Displays all items
         * 
         * @throw runtime_error Display is not set
        */
        void displayAllItems();

        /**
         * @brief Gets whether the display is refering to NULL, does not check if the object is still alive
         * 
         * @return true Display != NULL
         * @return false Display == NULL
        */
        bool getDisplayIsSet() const;
        
        /**
         * @brief Removes a displayable item from the queue
         * 
         * @param item 
        */
        void removeFromRenderQueue(const IDisplayable* item);

        /**
         * @brief Renders all items in the display's buffer
         * 
         * @throw runtime_error Display was never set
        */
        void render();

        /**
         * @brief Set the Display object
         * 
         * @param display A pointer to the new display, keep the item alive as long as you're using it
        */
        void setDisplay(IDisplay* display);

        private:
        IDisplay* display;
        std::vector<const IDisplayable*> items;
        std::vector<std::string> textRender;

        DisplayManager();
    };  
}

#endif