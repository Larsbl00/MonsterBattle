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

    InputReader::~InputReader()
    {
        //Restore the attributes
        tcsetattr(fileno(stdin), TCSANOW, &this->oldAttributes);
    }

    void InputReader::update()
    {   
        fd_set set;
        struct timeval timeout = {.tv_sec=0, .tv_usec=100};

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

        int selectResponse = select(fileno(stdin) + 1, &set, NULL, NULL, &timeout);

        if (selectResponse <= EOF) 
        {
            throw std::runtime_error("Cannot set timeout for stdin");
        }
        else if(selectResponse > 0) 
        {
            char readChar;
            read(fileno(stdin), &readChar, sizeof(readChar));
            this->delegate.onKeyPress(fgetc(stdin));
        }
    }

    void InputReader::setDelegate(InputDelegate& delegate)
    {
        this->delegate = delegate;
    }
}