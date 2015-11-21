//
//  Move.h
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-19.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#ifndef __TypeChart__Move__
#define __TypeChart__Move__

#include <iostream>
#include <vector>
#include <sstream>

class Move
{
private:
    int moveID;
    std::string name;
    std::string type;
    int maxPP;
    int currentPP;
    int power;
    int accuracy; //Note a move that has no accuracy this value is a 0
    bool physOrSpec; //true=physical false=special
    int statChange; //Number of stages changed (+- 1 or +-2) Note I dont think there are any attacks that raise 3 stages but ill have to make a small change in AttackCalc if there is
    bool statUser; //false=self true=foe
    std::string targetStat;
    int changeChance;
    bool disabled;
public:
    Move(std::vector<std::string> *moveInfo, int moveID);
    Move(); //Struggle contructor
    int getAccuracy();
    std::string getType();
    bool getPhysOrSpec();
    int getPower();
    int getStatChange();
    bool getStatUser();
    std::string getTargetStat();
    int getChangeChance();
    int useMove(); //Should be a loop that repeats until true;  0=Fine 1=Disalbed 2=Out of PP of selected move 3=Struggle
    int getMoveID();
    int getMaxPP();
    int getCurrentPP();
    std::string getName();
    void setPP(int value);
};

#endif /* defined(__TypeChart__Move__) */
