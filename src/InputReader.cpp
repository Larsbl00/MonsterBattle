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
    this->newAttributes &= ~(ECHO | ICANNON);
    this->newAttributes.c_cc[VTIME] = 0;
    this->newAttributes.c_cc[VMIN] = 0;

    //Set the new attributes
    tcsetattr(fileno(stdin), TCSANOW, this->newAttributes);
}

InputReader::~InputReader()
{
    //Restore the attributes
    tcsetattr(fileno(stdin), TCSANOW, this->oldAttributes);
}

void InputReader::update()
{
    char input = fgetc(stdin);
    if (input >= 0) this->delegate.onKeyPress(&input);
}

void InputReader::setDelegate(InputDelegate& delegate)
{
    this->delegate = delegate;
}