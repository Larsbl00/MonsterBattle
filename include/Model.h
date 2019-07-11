/**
 * @file Model.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-26
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <ostream>
#include <stdexcept>
#include <fstream>

#include "Color.h"
#include "Sprite.h"
#include "RaiiFileHandle.h"

namespace monsterbattle
{
    class Model: public Sprite
    {
        public:
        Model();
        Model(const std::string& modelFile);
        Model(const Color& color);
        Model(const std::string& modelFile, const Color& color);
        virtual ~Model() noexcept = default;

        const std::string& getFileName() const;

        void load();
        void load(const std::string& modelFile);

        private:
        std::string fileName;
    };
}

#endif
