//
//  FileReader.h
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-22.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#ifndef __TypeChart__FileReader__
#define __TypeChart__FileReader__

#include <iostream>
#include <fstream>
#include <vector>
#include "StoredStats.h"

class FileReader
{
private:
    //std::vector<std::string> pkmnStats;
    std::vector<std::string> moveStats;
    std::vector<StoredStats> storedPkmnStats;
public:
    //Returns true if file read successfully and stores the information
    bool readPokemonFile(std::string fileName);
    bool readMoveFile(std::string fileName);
    std::vector<std::string>* getMoveInfo();
    StoredStats* getPokemonStats(int index);
};

#endif /* defined(__TypeChart__FileReader__) */
