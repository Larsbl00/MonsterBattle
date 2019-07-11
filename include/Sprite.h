/**
 * @file Sprite.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <algorithm>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Color.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"

namespace monsterbattle
{
    class Sprite: public IDisplayable 
    {
        public:
        using Data_t = char;
        using Buffer_t = std::vector<std::vector<Sprite::Data_t>>;

        const static constexpr auto EmptyChar = ' ';
        const static constexpr auto& DefaultColor = monsterbattle::Color::Black;

        Sprite() = default;
        Sprite(const Vector2i32& size);
        Sprite(const Vector2i32& location, const Vector2i32& size);
        Sprite(const Vector2i32& size, const Color& color);
        Sprite(const Vector2i32& location, const Vector2i32& size, const Color& color);
        Sprite(const Buffer_t& buffer);
        Sprite(Buffer_t&& buffer) noexcept;
        Sprite(const Buffer_t& buffer, const Color& color);
        Sprite(Buffer_t&& buffer, const Color& color) noexcept;
        Sprite(const Vector2i32& location, const Buffer_t& buffer);
        Sprite(const Vector2i32& location, Buffer_t&& buffer) noexcept;
        Sprite(const Vector2i32& location, const Buffer_t& buffer, const Color& color);
        Sprite(const Vector2i32& location, Buffer_t&& buffer, const Color& color) noexcept;
        Sprite(Sprite&& other) noexcept;
        Sprite(const Sprite& other) = default;
        virtual ~Sprite() noexcept = default;

        /**
         * @brief Displays the sprite on a display
         * 
         * @param display 
        */
        void display(IDisplay& display);

        /**
         * @brief Flips a sprite horizontal, i.e. turning
         * 
         * ^
         * _
         * 
         * into 
         * 
         * _
         * 
         * v
         * 
        */
        void flipHorizontal();

        /**
         * @brief Flips the sprite vertically, i.e. turning XE into 3X
         * 
        */
        void flipVertical();

        const Buffer_t& getBuffer() const;
        const Color& getColor() const;

        void move(const Vector2i32& direction);
        void setBuffer(const Buffer_t& newBuffer);
        void setBuffer(const Vector2i32& position, Sprite::Data_t value);
        void setBuffer(const Vector2i32& position, const Vector2i32& size, Sprite::Data_t value);
        void setColor(const Color& color);

        protected:
        Buffer_t buffer;
        Color color;
        Vector2i32 location;
        Vector2i32 size;
    };
}
#endif