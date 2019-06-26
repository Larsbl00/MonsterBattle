/**
 * @file Sprite.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Sprite.h"

namespace monsterbattle 
{
    /*****************************
     * 
     * Constructors
     * 
     */
    Sprite::Sprite(const Vector2i32& size):
        location(), size(size)
    {
        this->buffer.resize(size.y);
        for (auto& y : this->buffer)
        {
            y.resize(size.x);
        }
    }

    Sprite::Sprite(const Vector2i32& location, const Vector2i32& size):
        location(location), size(size)
    {
        this->buffer.resize(size.y);
        for (auto& y : this->buffer)
        {
            y.resize(size.x);
        }
    }

    Sprite::Sprite(const Buffer_t& buffer):
        buffer(buffer), location(), size(buffer[0].size(), buffer.size())
    {}

    Sprite::Sprite(Buffer_t&& buffer) noexcept:
        buffer(buffer), location(), size(buffer[0].size(), buffer.size())
    {}

    Sprite::Sprite(const Vector2i32& location, const Buffer_t& buffer):
        buffer(buffer), location(location), size(buffer[0].size(), buffer.size())
    {}

    Sprite::Sprite(const Vector2i32& location, Buffer_t&& buffer) noexcept:
        buffer(buffer), location(location), size(buffer[0].size(), buffer.size())
    {}


    /************************
     * 
     * Functions
     * 
     */
    void Sprite::display(IDisplay& display)
    {
        size_t yIterator = 0;
        for (auto& y : this->buffer)
        {
            size_t xIterator = 0;
            for (auto& x : y)
            {
                display.setPixel(Vector2i32(this->location.x + xIterator, this->location.y + yIterator), x);
                xIterator++;
            }
            yIterator++;
        }

    }

    void Sprite::move(const Vector2i32& direction) { this->location += direction; }

    void Sprite::setBuffer(const Sprite::Buffer_t& newBuffer)
    {
        this->buffer = newBuffer;
        this->size = Vector2i32(newBuffer[0].size(), newBuffer.size());
    }

    void Sprite::setBuffer(const Vector2i32& position, Sprite::Data_t value)
    {
        if (position.x >= this->size.x || position.x < 0) throw std::out_of_range("X-position is invallid");
        if (position.y >= this->size.y || position.y < 0) throw std::out_of_range("Y-position is invallid");

        this->buffer[position.y][position.x] = value;
    }

    void Sprite::setBuffer(const Vector2i32& position, const Vector2i32& size, Sprite::Data_t value)
    {
        if (position.x >= this->size.x || position.x < 0 || position.x + size.x >= this->size.x || position.x + size.x < 0)
        {
            throw std::out_of_range("The width does not fit within the buffer");
        }

        if (position.y >= this->size.y || position.y < 0 || position.y + size.y >= this->size.y || position.y + size.y < 0)
        {
            throw std::out_of_range("The height does not fit within the buffer");
        }

        //Set __all__ values equal to the given value
        for (auto y = this->buffer.begin() + position.y; y != this->buffer.begin() + (position.y + size.y); y++)
        {
            for (auto x = y->begin() + position.x; x != y->begin() + (position.x + size.x); x++)
            {
                *x = value;
            }
        }
    }
}