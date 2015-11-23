//
//  StoredStats.h
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-20.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#ifndef __TypeChart__StoredStats__
#define __TypeChart__StoredStats__

#include <iostream>
#include <vector>
#include <sstream>

//Each of these stores all the stats for one potential pokemon

class StoredStats
{
private:
    int ID;
    std::string name;
    std::string type1;
    std::string type2;
    int maxhp;
    int minhp;
    int maxAtt;
    int minAtt;
    int maxSpAtt;
    int minSpAtt;
    int maxDef;
    int minDef;
    int maxSpDef;
    int minSpDef;
    int maxSpeed;
    int minSpeed;
    int move1;
    int move2;
    int move3;
    int move4;
public:
    //StoredStats(std::vector<std::string>* statStrings, int index);
    StoredStats(std::string statString);
    int getID();
    std::string getName();
    std::string getType1();
    std::string getType2();
    int getMaxhp();
    int getMinhp();
    int getMaxAtt();
    int getMinAtt();
    int getMaxSpAtt();
    int getMinSpAtt();
    int getMaxDef();
    int getMinDef();
    int getMaxSpDef();
    int getMinSpDef();
    int getMaxSpeed();
    int getMinSpeed();
    int getMove1();
    int getMove2();
    int getMove3();
    int getMove4();
};

#endif /* defined(__TypeChart__StoredStats__) */
