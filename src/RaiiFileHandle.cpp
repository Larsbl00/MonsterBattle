/**
 * @file RaiiFileHandle.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-26
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "RaiiFileHandle.h"

namespace monsterbattle
{
    RaiiFileHandle::RaiiFileHandle(const std::string& fileName)
    {
        stream.open(fileName);
    }

    RaiiFileHandle::~RaiiFileHandle() noexcept 
    {
        this->close();
    }

    void RaiiFileHandle::close() { if (this->stream.is_open()) this->stream.close(); }
    void RaiiFileHandle::open(const std::string& fileName) { this->close(); this->stream.open(fileName); }
}