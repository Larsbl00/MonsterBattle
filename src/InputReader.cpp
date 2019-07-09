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
    InputReader::InputReader(InputDelegate& delegate):
        delegate(delegate)
    {
        //Copy old attributes
        tcgetattr(fileno(stdin), &this->oldAttributes);

        //Edit the attributes
        memcpy(&this->newAttributes, &this->oldAttributes, sizeof(this->newAttributes));
        this->newAttributes.c_lflag &= ~(ECHO | ICANON);

        //Set the new attributes
        tcsetattr(fileno(stdin), TCSANOW, &this->newAttributes);
    }

    InputReader::~InputReader() noexcept
    {
        //Restore the attributes
        tcsetattr(fileno(stdin), TCSANOW, &this->oldAttributes);
    }

    void InputReader::update()
    {   
        fd_set set;
        struct timeval timeout = {
            .tv_sec=INPUT_READER_TIMEOUT_SECONDS, 
            .tv_usec=INPUT_READER_TIMEOUT_MICROS
        };

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

        auto result = select(fileno(stdin) + 1, &set, NULL, NULL, &timeout);
        if (result < 0) 
        {
            throw std::runtime_error("Cannot set the timour on the input reader");
        }
        else if (result > 0)
        {
            char data;
            read(fileno(stdin), &data, sizeof(data));
            this->delegate.onKeyPress(data);
        }
    }

    void InputReader::setDelegate(InputDelegate& delegate)
    {
        this->delegate = delegate;
    }
}