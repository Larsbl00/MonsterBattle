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

#include "Singleton.h"
#include "Type.h"

namespace monsterbattle
{
    class TypeWeaknessManager:
        public Singleton<TypeWeaknessManager>
    {
        // Make the singleton a friend so it can access the private destructor 
        friend Singleton;

        public:
        
        const static constexpr float WeaknessMultiplier = 2.0;

        TypeWeaknessManager(const TypeWeaknessManager& other) = delete;
        ~TypeWeaknessManager() noexcept = default;

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