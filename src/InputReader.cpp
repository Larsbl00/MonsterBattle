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
    this->delegate.onKeyPress(fgetc(stdin));
}

void InputReader::setDelegate(InputDelegate& delegate)
{
    this->delegate = delegate;
}