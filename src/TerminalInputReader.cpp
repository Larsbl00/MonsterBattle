/**
 * @file TerminalInputReader.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-25
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "TerminalInputReader.h"

namespace monsterbattle
{
    /*******************
     * 
     * Costructors
     * 
     */

    TerminalInputReader::TerminalInputReader()
    {
        //Copy old attributes
        tcgetattr(fileno(stdin), &this->oldAttributes);

        //Edit the attributes
        memcpy(&this->newAttributes, &this->oldAttributes, sizeof(this->newAttributes));
        this->newAttributes.c_lflag &= ~(ECHO | ICANON);

        //Set the new attributes
        tcsetattr(fileno(stdin), TCSANOW, &this->newAttributes);
    }

    TerminalInputReader::~TerminalInputReader() noexcept
    {
        tcsetattr(fileno(stdin), TCSANOW, &this->oldAttributes);
    }

    /******************
     * 
     * Public Functions
     * 
     */

    void TerminalInputReader::update()
    {
        fd_set set;
        struct timeval timeout = TerminalInputReader::Timeout;

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

        auto result = select(fileno(stdin) + 1, &set, NULL, NULL, &timeout);
        if (result < 0) 
        {
            throw std::runtime_error("Cannot set the timout on the input reader");
        }
        else if (result > 0)
        {
            char data;
            auto readBytes = read(fileno(stdin), &data, sizeof(data));

            if (readBytes != sizeof(data)) 
            {
                throw std::runtime_error("Error Reading user input");
            }

            if (this->delegate != nullptr) this->delegate->onKeyPress(data);
        }
    }
}