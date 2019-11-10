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
#include <vector>

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

        /**
         * @brief Loads the data from the file it is initialized with
         * 
         * @throw runtime_error Cannot find file
         * 
        */
        void load();

        /**
         * @brief Loads the data from a given file
         * 
         * @param modelFile 
         * 
         * @throw runtime_error Cannot find file
        */
        void load(const std::string& modelFile);

        private:
        std::string fileName;
    };
}

#endif
