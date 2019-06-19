/**
 * @file InputReader.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <iostream>
#include <cstring>
#include <termios.h>


#include "InputDelegate.h"

namespace monsterbattle
{
    class InputReader
    {
        public:
        InputReader(InputDelegate& delegate);
        ~InputReader();

        void update();

        /**
         * @brief Sets the input delegation
         * 
         */
        void setDelegate(InputDelegate& delegate);

        private:
        InputDelegate& delegate;

        struct termios newAttributes;
        struct termios oldAttributes;
    };
}

#endif