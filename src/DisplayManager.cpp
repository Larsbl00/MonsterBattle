/**
 * @file DisplayManager.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "DisplayManager.h"

namespace monsterbattle
{
    /*****************************************
     * 
     * Constructor
     * 
     */
    DisplayManager::DisplayManager():
        display(nullptr)
    {

    }

    DisplayManager& DisplayManager::getInstance()
    {
        static DisplayManager manager;
        return manager;
    }

    void DisplayManager::addToRenderQueue(IDisplayable* item)
    {
        if (item == nullptr) throw std::invalid_argument("Cannot add NULL to items");
    
        this->items.push_back(item);
    }  

    void DisplayManager::displayAllItems()
    {
        if (this->display == nullptr) throw std::runtime_error("Display was never set");
        
        this->display->display();
    }

    void DisplayManager::removeFromRenderQueue(IDisplayable* item)
    {
        this->items.erase(std::remove(this->items.begin(), this->items.end(), item), this->items.end());
    }


    void DisplayManager::render()
    {
        if (this->display == nullptr) throw std::runtime_error("Display was never set");

        for (const auto& item : this->items)
        {
            item->display(*(this->display));
        }
    }


    void DisplayManager::setDisplay(IDisplay* display)
    {
        this->display = display;
    }
}