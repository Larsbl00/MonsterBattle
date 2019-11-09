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
    {}

    void DisplayManager::addToRenderQueue(const IDisplayable* item)
    {
        if (item == nullptr) throw std::invalid_argument("Cannot add NULL to items");
    
        this->items.push_back(item);
    }  

    void DisplayManager::displayAllItems()
    {
        if (this->display == nullptr) throw std::runtime_error("Display was never set");
        
        this->display->display();
    }

    const IDisplay* DisplayManager::getDisplay() const 
    {
        return this->display;
    }

    bool DisplayManager::getDisplayIsSet() const 
    {
        return this->display != nullptr;
    }

    void DisplayManager::removeFromRenderQueue(const IDisplayable* item)
    {
        this->items.erase(std::remove(this->items.begin(), this->items.end(), item), this->items.end());
    }

    void DisplayManager::render()
    {
        if (this->display == nullptr) throw std::runtime_error("Display was never set");

        for (const auto& item : this->items)
        {
            //If item is null remove it
            if (item == nullptr)
            {
                this->removeFromRenderQueue(item);
            }
            else 
            {
                item->display(*(this->display));
            }
        }
    }


    void DisplayManager::setDisplay(IDisplay* display)
    {
        this->display = display;
    }
}