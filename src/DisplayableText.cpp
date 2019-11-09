/**
 * @file DisplayableText.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-09-08
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "DisplayableText.h"
#include "IDisplay.h"

namespace monsterbattle
{
    /******************
     * 
     * Constructors
     * 
     */

    DisplayableText::DisplayableText(const std::string& text, const Vector2i32& location, const Color& color):
        color(color), isHidden(false), location(location), text(text)
    {}


    /********************8
     * 
     * Public functions
     * 
     */
    void DisplayableText::display(IDisplay& display) const
    {
        //TODO The line below throws a segfault, fix it
        if (!this->getIsHidden()) display.putString(this->location, this->text, this->color);
    }

    bool DisplayableText::getIsHidden() const { return this->isHidden; }

    void DisplayableText::hide()
    {   
        this->isHidden = true;
    }

    void DisplayableText::move(const Vector2i32& direction) { this->location += direction; }
    void DisplayableText::moveTo(const Vector2i32& location) { this->location = location; }

    
    void DisplayableText::setColor(const Color& color) { this->color = color; }

    void DisplayableText::setText(const std::string& text) { this->text = text; }

    void DisplayableText::show()
    {
        this->isHidden = false;
    }   
}