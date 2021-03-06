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
#include "IMoveable.h"
#include "Vector.h"

namespace monsterbattle
{
    class Sprite: 
        public IDisplayable,
        public IMoveable
    {
        public:
        using Data_t = char;
        using Buffer_t = std::vector<std::vector<Sprite::Data_t>>;

        static constexpr auto EmptyChar = ' ';
        static constexpr auto& DefaultColor = monsterbattle::Color::Black;

        Sprite();
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
        virtual void display(IDisplay& display) const override;

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

        void move(const Vector2i32& direction) override;
        void moveTo(const Vector2i32& location) override;
        
        void setBuffer(const Buffer_t& newBuffer);
        /**
         * @brief Set the Buffer object
         * 
         * @param position 
         * @param value 
         * 
         * @throw out_of_range Either index of 'position' could be out of range 
        */
        void setBuffer(const Vector2i32& position, Sprite::Data_t value);

        /**
         * @brief Set the Buffer object
         * 
         * @param position 
         * @param size 
         * @param value 
         * 
         * @throw out_of_range Either index of 'position' could be out of range 
        */
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