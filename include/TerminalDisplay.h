/**
 * @file TerminalDisplay.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef TERMINAL_DISPLAY_H
#define TERMINAL_DISPLAY_H

#include <sys/ioctl.h>
#include <cstdio>
#include <sstream>
#include <vector>

#include "AnsiEffects.h"
#include "CharColorPair.h"
#include "IDisplay.h"
#include "Color.h"
#include "Vector.h"

#define TERMINAL_DISPLAY_EMPTY_CHAR (' ')
#define TERMINAL_ANSI_FOREGROUND (38)
#define TERMINAL_ANSI_BACKGROUND (48)

namespace monsterbattle
{
    class TerminalDisplay: public IDisplay
    {
        public:
        
        using Pixel_t = CharColorPair;

        const static inline auto DefaultTerminalSettings = "\033[49m";
        static constexpr auto& BackgroundColor = monsterbattle::Color::Black;
        static constexpr char EmptyChar = TERMINAL_DISPLAY_EMPTY_CHAR;

        /**
         * @brief Construct a new Terminal Display object
         * 
        */
        TerminalDisplay();

        /**
         * @brief Construct a new Terminal Display object
         * 
         * @param size 
        */
        TerminalDisplay(const Vector2i32& size);

        TerminalDisplay(const TerminalDisplay& other) = delete;

        ~TerminalDisplay() noexcept;

        void clear() override;
        void display() override;
        const Vector2i32& getSize() const;
        void setPixel(const Vector2i32& pixel, char value) override;
        void setPixel(const Vector2i32& pixel, const monsterbattle::Color& color) override;
        void setPixel(const Vector2i32& pixel, char value, const monsterbattle::Color& color) override;
        void putString(const Vector2i32& pixel, const std::string& string) override;
        void putString(const Vector2i32& pixel, const std::string& string, const monsterbattle::Color& color) override;

        private:
        Vector2i32 size;
        Pixel_t** buffer;
        monsterbattle::Color previouslyUsedColor;

        void addTerminalEffect(monsterbattle::text::AnsiTextEffect effect) const;
        void ansiStart() const;
        void ansiEnd() const;
        void setBackgroundColor(const monsterbattle::Color& color) const;
        void setForegroundColor(const monsterbattle::Color& color) const;
        void resetTerminal() const;

    };
}

#endif