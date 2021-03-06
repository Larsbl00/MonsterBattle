/**
 * @file RaiiFileHandle.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-26
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef RAII_FILE_HANDLER_H
#define RAII_FILE_HANDLER_H

#include <string>
#include <fstream>

namespace monsterbattle
{
    class RaiiFileHandle: public std::fstream
    {
        public:
        RaiiFileHandle(const std::string& fileName);
        ~RaiiFileHandle() noexcept;
    };

}

#endif