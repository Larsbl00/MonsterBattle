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
#include <unordered_map>

#include "Type.h"


namespace monsterbattle
{
    class TypeWeaknessManager
    {
        public:
        const static constexpr float WeaknessMultiplier = 2.0;

        ~TypeWeaknessManager() noexcept;

        static TypeWeaknessManager& getInstance();

        /**
         * @brief Get the weaknesses of any given monsterbattle::Type
         * 
         * @param type 
         * @return std::vector<Type>& 
        */
        std::vector<Type>& getWeaknesses(Type type);

        private: 
        TypeWeaknessManager();

        std::unordered_map<Type, std::vector<Type>> weaknessMap;
    };
}

#endif