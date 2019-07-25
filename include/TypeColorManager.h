/**
 * @file TypeColorManager.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-25
 * 
 * @copyright Copyright (c) 2019
 * 
*/
#ifndef TYPE_COLOR_MANAGER_H
#define TYPE_COLOR_MANAGER_H

#include <unordered_map>

#include "Color.h"
#include "Singleton.h"
#include "Type.h"

namespace monsterbattle
{
    class TypeColorManager: public Singleton<TypeColorManager>
    {
        friend Singleton;

        public:

        TypeColorManager(const TypeColorManager& other) = delete;
        ~TypeColorManager() noexcept = default;

        const Color& getColorFromType(Type type);

        private:

        std::unordered_map<Type, Color> typeColorMap;

        TypeColorManager();
    };
}

#endif