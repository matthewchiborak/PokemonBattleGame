//
//  Move.cpp
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-19.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#include "Move.h"

Move::Move(std::vector<std::string> *moveInfo, int moveID)
{
    std::vector<std::string> parsedStrings;
    std::stringstream ss(moveInfo->at(moveID));
    
    std::string temp="";
    char i;
    
    while(ss>>i)
    {
        temp+=i;
        
        if(ss.peek()==',')
        {
            ss.ignore();
            parsedStrings.push_back(temp);
            temp="";
        }
    }
    parsedStrings.push_back(temp);

    
    //Split the string at the right ID location
    disabled=false;
    this->moveID=std::stoi(parsedStrings.at(0));
    name=parsedStrings.at(1);
    type=parsedStrings.at(2);
    maxPP=std::stoi(parsedStrings.at(3));
    currentPP=std::stoi(parsedStrings.at(3));
    power=std::stoi(parsedStrings.at(4));
    accuracy=std::stoi(parsedStrings.at(5)); //Note a move that has no accuracy this value is a 0
    physOrSpec=std::stoi(parsedStrings.at(6))==1; //true=physical false=special
    statChange=std::stoi(parsedStrings.at(7)); //Number of stages changed (+- 1 or +-2) Note I dont think there are any attacks that raise 3 stages but ill have to make a small change in AttackCalc if there is
    statUser=std::stoi(parsedStrings.at(8))==1; //false=self true=foe
    targetStat=parsedStrings.at(9);
    changeChance=std::stoi(parsedStrings.at(10));
    
    
}

Move::Move()
{
    moveID=0;
    name="Struggle";
    type="Normal";
    maxPP=1;
    currentPP=1;
    power=50;
    accuracy=0; //Note a move that has no accuracy this value is a 0
    physOrSpec=1; //true=physical false=special
    statChange=1; //Number of stages changed (+- 1 or +-2) Note I dont think there are any attacks that raise 3 stages but ill have to make a small change in AttackCalc if there is
    statUser=0; //false=self true=foe
    targetStat="Recoil";
    changeChance=100;
    disabled=false;
}

int Move::useMove()
{
    if(disabled)
    {
        return 1;
    }
    if (currentPP==0) {
        return 2;
    }
    currentPP-=1;
    return 0;
}

int Move::getMoveID()
{
    return moveID;
}

int Move::getAccuracy()
{
    return accuracy;
}

std::string Move::getType()
{
    return type;
}

void Move::setPP(int value)
{
    currentPP=value;
}

bool Move::getPhysOrSpec()
{
    return physOrSpec;
}

std::string Move::getName()
{
    return name;
}

int Move::getPower()
{
    return power;
}

int Move::getStatChange()
{
    return statChange;
}

bool Move::getStatUser()
{
    return statUser;
}

std::string Move::getTargetStat()
{
    return targetStat;
}

int Move::getChangeChance()
{
    return changeChance;
}

int Move::getMaxPP()
{
    return maxPP;
}
int Move::getCurrentPP()
{
    return currentPP;
}