//
//  FileReader.cpp
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-22.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#include "FileReader.h"

bool FileReader::readPokemonFile(std::string fileName)
{
    std::string line;
    std::ifstream myFile(fileName);
    if(myFile.is_open())
    {
        while (getline(myFile, line))
        {
            storedPkmnStats.push_back(StoredStats(line));
        }
        myFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool FileReader::readMoveFile(std::string fileName)
{
    std::string line;
    std::ifstream myFile(fileName);
    if(myFile.is_open())
    {
        while (getline(myFile, line))
        {
            moveStats.push_back(line);
        }
        myFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string>* FileReader::getMoveInfo()
{
    return &moveStats;
}

StoredStats* FileReader::getPokemonStats(int index)
{
    return &storedPkmnStats.at(index);
}