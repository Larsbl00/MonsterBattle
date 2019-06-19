/**
 * @file TerminalDisplay.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "TerminalDisplay.h"

namespace monsterbattle 
{
    TerminalDisplay::TerminalDisplay()
    {
        struct winsize size;
        ioctl(fileno(stdout), TIOCGWINSZ, &size);
        this->size = Vector2i32(size.ws_col, size.ws_row);
    }

    TerminalDisplay::TerminalDisplay(const Vector2i32& size):
        size(size)
    {

    }

    TerminalDisplay::~TerminalDisplay()
    {

    }

    void TerminalDisplay::clear()
    {

    }

    const Vector2i32& TerminalDisplay::getSize() const
    {
        return this->size;
    }

    void TerminalDisplay::setPixel(const Vector2i32& location, char value)
    {
        std::cout << "Setting " << location << " to: " << value << std::endl;
    }
}