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

        /**
         * @brief Construct a new Displayable Text object
         * 
         * @param text Text to display
         * @param location Location to display the text
         * @param color Color of the displayed text
        */
        DisplayableText(const std::string& text, const Vector2i32& location, const Color& color);
        DisplayableText(const DisplayableText& other) = delete;
        ~DisplayableText() noexcept = default;

        void display(IDisplay& display) const override;
        bool getIsHidden() const;
        void hide();
        void move(const Vector2i32& direction) override;
        void setColor(const Color& color);
        void setText(const std::string& text);
        void show();

        private:
        Color color;
        bool isHidden;
        Vector2i32 location;
        std::string text;
    };
}

#endif