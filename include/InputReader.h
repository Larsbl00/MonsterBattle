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

//Check platform
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <termios.h>
#endif


#include "InputDelegate.h"

class InputReader
{
    public:
    InputReader(InputDelegate& delegate);
    ~InputReader() noexcept;

    void update();

    /**
     * @brief Sets the input delegation
     * 
     */
    void setDelegate(InputDelegate& delegate);

    private:
    InputDelegate& delegate;

    #ifdef _WIN32
    
    #else
    struct termios newAttributes;
    struct termios oldAttributes;
    #endif
};

#endif