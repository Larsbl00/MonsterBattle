/**
 * @file DisplayAbleText.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-09-08
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef DISPLAYABLE_TEXT_H
#define DISPLAYABLE_TEXT_H

#include "IDisplayable.h"
#include "IMoveable.h"
#include "Vector.h"

namespace monsterbattle
{
    class DisplayableText: 
        public IDisplayable,
        public IMoveable
    {
        public:

        DisplayableText(const std::string& text, const Vector2i32& location, const Color& color);
        DisplayableText(const DisplayableText& other) = delete;
        ~DisplayableText() noexcept;

        void display(IDisplay& display) override;
        void move(const Vector2i32& direction) override;
        void setColor(const Color& color);
        void setText(const std::string& text);

        private:
        Color color;
        Vector2i32 location;
        std::string text;
    };
}

#endif