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
        uint32_t width = size.ws_row;
        uint32_t height = size.ws_col;

        this->size = Vector2i32(width, height);

        std::cout << size.ws_col << 'x' << size.ws_row << std::endl;

        std::cout << this->size << std::endl;

        std::cout << this->size.x << 'x' << this->size.y << std::endl;
    }

    TerminalDisplay::TerminalDisplay(const Vector2i32& size):
        size(size)
    {

    }

    TerminalDisplay::~TerminalDisplay() noexcept
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