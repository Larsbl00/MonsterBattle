/**
 * @file TypeWeaknessManager.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TYPE_WEAKNESS_MANAGER_H
#define TYPE_WEAKNESS_MANAGER_H

#include <vector>
#include <map>

#include "Type.h"


namespace monsterbattle
{
    class TypeWeaknessManager
    {
        public:
        ~TypeWeaknessManager() noexcept;

        static TypeWeaknessManager& getInstance();

        std::vector<Type>& getWeaknesses(Type type);

        private: 
        TypeWeaknessManager();

        std::map<Type, std::vector<Type>> weaknessMap;
    };
}

#endif