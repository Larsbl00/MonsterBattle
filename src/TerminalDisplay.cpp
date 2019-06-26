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
    TerminalDisplay::TerminalDisplay():
        buffer(nullptr)
    {
        struct winsize size;
        ioctl(fileno(stdout), TIOCGWINSZ, &size);

        this->size = Vector2i32(size.ws_col, size.ws_row);

        //alloc y
        this->buffer = new char*[this->size.y];
        //for each y alloc x
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            this->buffer[y] = new char[this->size.x];
        }
        

        this->clear();
    }

    TerminalDisplay::TerminalDisplay(const Vector2i32& size):
        size(size), buffer(new char*[size.y])
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            this->buffer[y] = new char[this->size.x];
        }

        this->clear();
    }

    TerminalDisplay::~TerminalDisplay() noexcept
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            delete[] this->buffer[y];
            this->buffer[y] = nullptr;
        }

        delete[] this->buffer;
        this->buffer = nullptr;
    }

    void TerminalDisplay::clear()
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            for (decltype(this->size.x) x = 0; x < this->size.x; x++)
            {
                this->buffer[y][x] = TERMINAL_DISPLAY_EMPTY_CHAR;
            }
        }
    }

    void TerminalDisplay::display()
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            for (decltype(this->size.x) x = 0; x < this->size.x; x++)
            {
                putc(this->buffer[y][x], stdout);
            }

            putc('\n', stdout);
        }
    }

    const Vector2i32& TerminalDisplay::getSize() const
    {
        return this->size;
    }

    void TerminalDisplay::setPixel(const Vector2i32& location, char value)
    {
        this->buffer[location.y][location.x] = value;
    }
}