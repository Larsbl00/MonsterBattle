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
    const std::string TerminalDisplay::DefaultTerminalSettings = "\033[49m";

    TerminalDisplay::TerminalDisplay():
        buffer(nullptr)
    {
        struct winsize size;
        ioctl(fileno(stdout), TIOCGWINSZ, &size);

        this->size = Vector2i32(size.ws_col, size.ws_row);

        //alloc y
        this->buffer = new TerminalDisplay::Pixel_t*[this->size.y];
        //for each y alloc x
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            this->buffer[y] = new TerminalDisplay::Pixel_t[this->size.x];
        }
        

        this->clear();
    }

    TerminalDisplay::TerminalDisplay(const Vector2i32& size):
        size(size), buffer(new TerminalDisplay::Pixel_t*[size.y])
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            this->buffer[y] = new TerminalDisplay::Pixel_t[this->size.x];
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

        this->resetTerminal();
    }

    void TerminalDisplay::clear()
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            for (decltype(this->size.x) x = 0; x < this->size.x; x++)
            {
                auto& pixel = this->buffer[y][x];
                pixel.character = TerminalDisplay::EmptyChar;
                pixel.color = TerminalDisplay::BackgroundColor;
            }
        }
    }

    void TerminalDisplay::display()
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            for (decltype(this->size.x) x = 0; x < this->size.x; x++)
            {
                //Get pixel
                auto& pixel = this->buffer[y][x];
                //Flag for effects
                this->ansiStart();
                this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_NORMAL);

                //If empty, render it as background
                if (pixel.character == TerminalDisplay::EmptyChar) this->setBackgroundColor(pixel.color);
                else this->setForegroundColor(pixel.color);

                //End the sequence
                this->ansiEnd();

                //Add the item
                std::cout << pixel.character;
                
                //Reset for next user
                this->resetTerminal();
            }

            std::cout << std::endl;
        }
    }

    const Vector2i32& TerminalDisplay::getSize() const
    {
        return this->size;
    }

    void TerminalDisplay::setPixel(const Vector2i32& pixel, char value)
    {
        this->buffer[pixel.y][pixel.x].character = value;
        this->buffer[pixel.y][pixel.x].color = monsterbattle::colors::Black;
    }

    void TerminalDisplay::setPixel(const Vector2i32& pixel, const monsterbattle::colors::Color& color)
    {
        this->buffer[pixel.y][pixel.x].color = color;
        this->buffer[pixel.y][pixel.x].character = TerminalDisplay::EmptyChar;
    }

    void TerminalDisplay::setPixel(const Vector2i32& pixel, char value, const monsterbattle::colors::Color& color)
    {
        std::cout << "Setting " << pixel << " to: " << color << std::endl;
        this->buffer[pixel.y][pixel.x].character = value;
        this->buffer[pixel.y][pixel.x].color = color;
    }

    /*******************************
     * Private functions
     */
    
    void TerminalDisplay::addTerminalEffect(monsterbattle::text::AnsiTextEffect effect) const 
    {
        std::cout << effect << ';';
    }

    void TerminalDisplay::ansiStart() const
    {
        std::cout << "\033[";
    }

    void TerminalDisplay::ansiEnd() const
    {
        std::cout << 'm';
    }

    void TerminalDisplay::setBackgroundColor(const monsterbattle::colors::Color& color) const
    {
        this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_SET_BACKGROUND);
        std::cout << "2;" << (int)color.red << ';' << (int)color.green << ';' << (int)color.blue;
    }

    void TerminalDisplay::setForegroundColor(const monsterbattle::colors::Color& color) const
    {
        this->setBackgroundColor(TerminalDisplay::BackgroundColor);
        this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_SWAP_BACKGROUND_FOREGROUND);
        this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_SET_FOREGROUND);
        std::cout << "2;" << (int)color.red << ';' << (int)color.green << ';' << (int)color.blue;
    }
    
    void TerminalDisplay::resetTerminal() const
    {
        std::cout << TerminalDisplay::DefaultTerminalSettings;
    }

}