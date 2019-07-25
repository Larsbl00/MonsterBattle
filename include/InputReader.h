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

#include "InputDelegate.h"

namespace monsterbattle
{
    class InputReader
    {
        public:
        InputReader();
        InputReader(const InputReader& other) = delete;
        virtual ~InputReader() noexcept = default;

        virtual void update() = 0;

        /**
         * @brief Sets the input delegation
         * 
         */
        void setDelegate(InputDelegate* delegate);

        protected:
        InputDelegate* delegate;
    };
}

#endif