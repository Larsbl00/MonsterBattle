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
        buffer(nullptr), previouslyUsedColor(monsterbattle::Color::White)
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
        size(size), buffer(new TerminalDisplay::Pixel_t*[size.y]), previouslyUsedColor(monsterbattle::Color::White)
    {
        for (decltype(this->size.y) y = 0; y < this->size.y; y++)
        {
            this->buffer[y] = new TerminalDisplay::Pixel_t[this->size.x];
        }

        this->clear();
    }

    TerminalDisplay::~TerminalDisplay() noexcept
    {
        this->resetTerminal();
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

                //If the current color hasn't been used previously, flag for the color
                if (pixel.color != this->previouslyUsedColor)
                {
                    this->ansiStart();
                    this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_NORMAL);

                    //If empty, render it as background
                    if (pixel.character == TerminalDisplay::EmptyChar) this->setBackgroundColor(pixel.color);
                    else this->setForegroundColor(pixel.color);

                    //End the sequence
                    this->ansiEnd();
                }

                std::cout << pixel.character;
                
                this->previouslyUsedColor = pixel.color;
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
        this->buffer[pixel.y][pixel.x].color = TerminalDisplay::BackgroundColor;
    }

    void TerminalDisplay::setPixel(const Vector2i32& pixel, const monsterbattle::Color& color)
    {
        this->buffer[pixel.y][pixel.x].color = color;
        this->buffer[pixel.y][pixel.x].character = TerminalDisplay::EmptyChar;
    }

    void TerminalDisplay::setPixel(const Vector2i32& pixel, char value, const monsterbattle::Color& color)
    {
        this->buffer[pixel.y][pixel.x].character = value;
        this->buffer[pixel.y][pixel.x].color = color;
    }

    void TerminalDisplay::putString(const Vector2i32& pixel, const std::string& string)
    {
        this->putString(pixel, string, TerminalDisplay::BackgroundColor);
    }

    void TerminalDisplay::putString(const Vector2i32& pixel, const std::string& string, const monsterbattle::Color& color)
    {
        size_t charsPlaced = 0;
        for (char c : string)
        {
            this->setPixel(Vector2i32(pixel.x + charsPlaced++, pixel.y), c, color);
        }
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

    void TerminalDisplay::setBackgroundColor(const monsterbattle::Color& color) const
    {
        this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_SET_BACKGROUND);
        std::cout 
        << "2;" 
        << (int)color.red * (color.alpha/255.0)
        << ';' 
        << (int)color.green * (color.alpha/255.0)
        << ';' 
        << (int)color.blue * (color.alpha/255.0);
    }

    void TerminalDisplay::setForegroundColor(const monsterbattle::Color& color) const
    {
        this->setBackgroundColor(TerminalDisplay::BackgroundColor);
        this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_SWAP_BACKGROUND_FOREGROUND);
        this->addTerminalEffect(monsterbattle::text::AnsiTextEffect::EFFECT_SET_FOREGROUND);
        std::cout 
        << "2;" 
        << (int)color.red * (color.alpha/255.0)
        << ';' 
        << (int)color.green * (color.alpha/255.0)
        << ';' 
        << (int)color.blue * (color.alpha/255.0);
    }
    
    void TerminalDisplay::resetTerminal() const
    {
        std::cout << TerminalDisplay::DefaultTerminalSettings;
    }

}