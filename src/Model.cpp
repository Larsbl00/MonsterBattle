/**
 * @file Model.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-26
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Model.h"

namespace monsterbattle
{
    Model::Model():
        Sprite()
    {}

    Model::Model(const std::string& modelFile):
        Sprite(),
        fileName(modelFile)
    {}

    Model::Model(const Color& color):
        Sprite()
    {
        this->setColor(color);
    }

    Model::Model(const std::string& modelFile, const Color& color):
        Sprite(),
        fileName(modelFile)
    {
        this->setColor(color);
    }
    
    const std::string& Model::getFileName() const { return this->fileName; }

    void Model::load()
    {
        Sprite::Buffer_t readBuffer;
        //Open a RAII filehandler to the file
        RaiiFileHandle fileHandler(this->getFileName());

        if(fileHandler.stream.is_open())
        {
            for (std::string readString; getline(fileHandler.stream, readString); )
            {
                std::vector<Sprite::Data_t> vec;
                for (char c : readString)
                {
                    vec.push_back(c);
                }
                
                readBuffer.push_back(vec);
            }
        }
        else 
        {
            throw std::runtime_error("Cannot find file: " + this->fileName);
        }

        fileHandler.close();

        Sprite::setBuffer(std::move(readBuffer));
    }

    void Model::load(const std::string& fileName)
    { 
        this->fileName = fileName; 
        this->load();
    }
}
