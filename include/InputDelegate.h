/**
 * @file InputDelegate.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef INPUT_DELEGATE_H
#define INPUT_DELEGATE_H

struct InputDelegate
{
    virtual ~InputDelegate(){}

    virtual void onKeyPress(char pressedKey) = 0;
    virtual void onKeyRelease(char releasedKey) = 0;
};

#endif