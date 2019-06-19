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

        void addToRenderQueue(const std::shared_ptr<IDisplayable>& item);
        void displayAllItems();
        void removeFromRenderQueue(const std::shared_ptr<IDisplayable>& item);
        void setDisplay(const std::shared_ptr<IDisplay>& display);

        private:
        std::shared_ptr<IDisplay> display;
        std::vector<std::shared_ptr<IDisplayable>> items;

        DisplayManager();
    };  
}

#endif