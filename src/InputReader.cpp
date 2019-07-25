/**
 * @file InputReader.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "InputReader.h"

namespace monsterbattle
{
    InputReader::InputReader():
        delegate(nullptr)
    {}

    void InputReader::setDelegate(InputDelegate* delegate)
    {
        this->delegate = delegate;
    }
}