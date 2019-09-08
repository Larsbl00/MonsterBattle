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
        color(color), location(location), text(text)
    {}


    /********************8
     * 
     * Public functions
     * 
     */
    void DisplayableText::display(IDisplay& display)
    {
        display.putString(this->location, this->text, this->color);
    }

    void DisplayableText::move(const Vector2i32& location) { this->location += location; }
    
    void DisplayableText::setColor(const Color& color) { this->color = color; }

    void DisplayableText::setText(const std::string& text) { this->text = text; }
    
}