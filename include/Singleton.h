/**
 * @file Singleton.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-23
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef SINGLETON_H
#define SINGLETON_H

namespace monsterbattle
{
    template<typename T>
    struct Singleton
    {
        Singleton(const Singleton& other) = delete;
        virtual ~Singleton() noexcept = default;

        static T& getInstance()
        {
            static T instance;
            return instance;
        }
        
        void operator=(const Singleton& other) = delete;
    };
    
}

#endif
