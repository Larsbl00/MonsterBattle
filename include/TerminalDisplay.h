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

#ifndef TERMINAL_DISPLAY
#define TERMINAL_DISPLAY

#include <sys/ioctl.h>

#include "IDisplay.h"
#include "Vector.h"

namespace monsterbattle
{
    class TerminalDisplay: public IDisplay
    {
        public:
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

        void clear();
        const Vector2i32& getSize() const;
        void setPixel(const Vector2i32& pixel, char value);

        private:
        Vector2i32 size;
    };
}

#endif