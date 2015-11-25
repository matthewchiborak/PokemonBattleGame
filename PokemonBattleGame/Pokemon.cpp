//
//  Pokemon.cpp
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-19.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#include "Pokemon.h"

Pokemon::Pokemon(StoredStats *pkmnInfo, std::vector<std::string> *moveInfo) //For creating your own Pokemon
{
    ID=(pkmnInfo->getID());
    name=(pkmnInfo->getName());
    type1=(pkmnInfo->getType1());
    type2=(pkmnInfo->getType2());
    
    int range = (pkmnInfo->getMaxhp()) - (pkmnInfo->getMinhp());
    int temp=(pkmnInfo->getMinhp())+rand()%range;
    
    maxHp=temp;
    hp=temp;
    previousTurnHp=temp;
    
    range = (pkmnInfo->getMaxAtt()) - (pkmnInfo->getMinAtt());
    att=(pkmnInfo->getMinAtt())+rand()%range;
    
    range = (pkmnInfo->getMaxSpAtt()) - (pkmnInfo->getMinSpAtt());
    spAtt=(pkmnInfo->getMinSpAtt())+rand()%range;
    
    range = (pkmnInfo->getMaxDef()) - (pkmnInfo->getMinDef());
    def=(pkmnInfo->getMinDef())+rand()%range;
    
    range = (pkmnInfo->getMaxSpDef()) - (pkmnInfo->getMinSpDef());
    spDef=(pkmnInfo->getMinSpDef())+rand()%range;
    
    range = (pkmnInfo->getMaxSpeed()) - (pkmnInfo->getMinSpeed());
    speed=(pkmnInfo->getMinSpeed())+rand()%range;
    
    evasion=(100);
    accuarcy=(100);
    currentStatis=0;
    isStruggling=false;
    move1= new Move(moveInfo, pkmnInfo->getMove1());
    move2=new Move(moveInfo, pkmnInfo->getMove2());
    move3=new Move(moveInfo, pkmnInfo->getMove3());
    move4=new Move(moveInfo, pkmnInfo->getMove4());
}

Pokemon::Pokemon(std::vector<std::string> *moveInfo, std::string stats)//For creating opponents Pokemon
{
    std::vector<std::string> parsedStrings;
    std::stringstream ss(stats);
    
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
    
    ID=std::stoi(parsedStrings.at(0));
    name=parsedStrings.at(1);
    type1=parsedStrings.at(2);
    type2=parsedStrings.at(3);
    hp=std::stoi(parsedStrings.at(4));
    maxHp=std::stoi(parsedStrings.at(5));
    previousTurnHp=std::stoi(parsedStrings.at(5));
    att=std::stoi(parsedStrings.at(6));
    spAtt=std::stoi(parsedStrings.at(7));
    def=std::stoi(parsedStrings.at(8));
    spDef=std::stoi(parsedStrings.at(9));
    speed=std::stoi(parsedStrings.at(10));
    evasion=100;
    accuarcy=100;
    currentStatis=0;
    isStruggling=false;
    move1=new Move(moveInfo, std::stoi(parsedStrings.at(11)));
    move2=new Move(moveInfo, std::stoi(parsedStrings.at(12)));
    move3=new Move(moveInfo, std::stoi(parsedStrings.at(13)));
    move4=new Move(moveInfo, std::stoi(parsedStrings.at(14)));
}

Pokemon::~Pokemon()
{
    delete move1;
    delete move2;
    delete move3;
    delete move4;
}

std::string Pokemon::sendCreationStats()
{
    std::string result="";
    result=result+std::to_string(ID)+",";
    result=result+name+",";
    result=result+type1+",";
    result=result+type2+",";
    result=result+std::to_string(hp)+",";
    result=result+std::to_string(maxHp)+",";
    result=result+std::to_string(att)+",";
    result=result+std::to_string(spAtt)+",";
    result=result+std::to_string(def)+",";
    result=result+std::to_string(spDef)+",";
    result=result+std::to_string(speed)+",";
    result=result+std::to_string(move1->getMoveID())+",";
    result=result+std::to_string(move2->getMoveID())+",";
    result=result+std::to_string(move3->getMoveID())+",";
    result=result+std::to_string(move4->getMoveID());
    
    return result;
}

void Pokemon::updateStats(std::string stats)
{
    std::vector<std::string> parsedStrings;
    std::stringstream ss(stats);
    
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
    
    previousTurnHp=hp;
    hp=std::stoi(parsedStrings.at(0));
    att=std::stoi(parsedStrings.at(1));
    spAtt=std::stoi(parsedStrings.at(2));
    def=std::stoi(parsedStrings.at(3));
    spDef=std::stoi(parsedStrings.at(4));
    speed=std::stoi(parsedStrings.at(5));
    evasion=std::stoi(parsedStrings.at(6));
    accuarcy=std::stoi(parsedStrings.at(7));
    currentStatis=std::stoi(parsedStrings.at(8));
    isStruggling=std::stoi(parsedStrings.at(9))==1;
    move1->setPP(std::stoi(parsedStrings.at(10)));
    move2->setPP(std::stoi(parsedStrings.at(11)));
    move3->setPP(std::stoi(parsedStrings.at(12)));
    move4->setPP(std::stoi(parsedStrings.at(13)));
}

int Pokemon::getMaxHP()
{
    return maxHp;
}

Move* Pokemon::getMove(int num)
{
    Move* wantedMove = nullptr;
    
    switch (num) {
        case 1:
            wantedMove = move1;
            break;
        case 2:
            wantedMove =move2;
            break;
        case 3:
            wantedMove =move3;
            break;
        case 4:
            wantedMove =move4;
            break;
    }
    return wantedMove;
}

std::string Pokemon::getType1()
{
    return type1;
}

std::string Pokemon::getType2()
{
    return type2;
}

double Pokemon::getEvasion()
{
    return evasion;
}

double Pokemon::getAccuracy()
{
    return accuarcy;
}

double Pokemon::getAtt()
{
    int tempAtt = att;
    if (currentStatis==1) {
        tempAtt=tempAtt/2;
    }
    return tempAtt;
}
double Pokemon::getDef()
{
    return def;
}
double Pokemon::getSpAtt()
{
    return spAtt;
}
double Pokemon::getSpDef()
{
    return spDef;
}
int Pokemon::getCurrentStatis()
{
    return currentStatis;
}
void Pokemon::setCurrentStatis(int statis)
{
    currentStatis=statis;
}

void Pokemon::removeConfusion()
{
    if (currentStatis==6||currentStatis==7) {
        currentStatis=0;
    }
}

void Pokemon::dealDamage(int damage)
{
    hp-=damage;
    if (hp<0) {
        hp=0;
    }
}

int Pokemon::getHP()
{
    return hp;
}

void Pokemon::changeStages(Move* usedMove, int* result, std::string* newStatus, int aOrD)
{
    int direct=usedMove->getStatChange();
    std::string stat=usedMove->getTargetStat();
    
    float sign = 1.5;
    if (direct<0) {
        sign=0.5;
    }
    
    for(int i=0; i<abs(direct); i++)
    {
        (*result)+=(100*aOrD);
    }
    
    if (stat=="Att")
    {
        (*result)+=10;
        for(int i=0; i<abs(direct); i++)
        {
            att=att*sign;
        }
    }
    else if (stat=="Def")
    {
        (*result)+=20;
        for(int i=0; i<abs(direct); i++)
        {
            def=def*sign;
        }
    }
    else if (stat=="SpAtt")
    {
        (*result)+=30;
        for(int i=0; i<abs(direct); i++)
        {
            spAtt=spAtt*sign;
        }
    }
    else if (stat=="SpDef")
    {
        (*result)+=40;
        for(int i=0; i<abs(direct); i++)
        {
            spDef*=sign;
        }
    }
    else if (stat=="Speed")
    {
        (*result)+=50;
        for(int i=0; i<abs(direct); i++)
        {
            speed*=sign;
        }
    }
    else if (stat=="Eva")
    {
        (*result)+=60;
        if (direct<0) {
            sign=(3/4);
        }
        else{
            sign=(4/3);
        }
        
        for(int i=0; i<abs(direct); i++)
        {
            evasion*=sign;
        }
    }
    else if (stat=="Acc")
    {
        (*result)+=70;
        if (direct<0) {
            sign=(3/4);
        }
        else{
            sign=(4/3);
        }
        
        for(int i=0; i<abs(direct); i++)
        {
            accuarcy*=sign;
        }
    }
    else if(stat=="Recoil")
    {
        dealDamage(maxHp/4);
        (*result)+=80;
    }
    
    
    if(currentStatis==0)
    {
    if(stat=="Burn")
    {
        setCurrentStatis(1);
        *newStatus="b";
    }
    else if(stat=="Freeze")
    {
        setCurrentStatis(2);
        *newStatus="f";
    }
    else if(stat=="Paralysis")
    {
        setCurrentStatis(3);
        *newStatus="p";
    }
    else if(stat=="Poison")
    {
        setCurrentStatis(4);
        *newStatus="a";
    }
    else if(stat=="Sleep")
    {
        setCurrentStatis(5);
        *newStatus="s";
    }
    else if(stat=="Confusion")
    {
        setCurrentStatis(7);
        *newStatus="c";
    }
    }
    else{
        *result=0;
    }
    
    //if(direct<0)
    //{
     //   (*result)*=-1;
    //}
}

int Pokemon::getSpeed()
{
    int tempSpeed=speed;
    if (currentStatis==3) {
        tempSpeed=tempSpeed-tempSpeed*(0.25f);
    }
    return tempSpeed;
}

int Pokemon::getID()
{
    return ID;
}

std::string Pokemon::getName()
{
    return name;
}

std::string Pokemon::getNewStats()
{
    std::string result="";
    
    result=result+std::to_string(hp)+",";
    result=result+std::to_string(att)+",";
    result=result+std::to_string(spAtt)+",";
    result=result+std::to_string(def)+",";
    result=result+std::to_string(spDef)+",";
    result=result+std::to_string(speed)+",";
    result=result+std::to_string(evasion)+",";
    result=result+std::to_string(accuarcy)+",";
    result=result+std::to_string(currentStatis)+",";
    result=result+std::to_string(isStruggling)+",";
    result=result+std::to_string(move1->getCurrentPP())+",";
    result=result+std::to_string(move2->getCurrentPP())+",";
    result=result+std::to_string(move3->getCurrentPP())+",";
    result=result+std::to_string(move4->getCurrentPP());
    
    return result;
    
}

int Pokemon::getPreviousTurnHp()
{
    return previousTurnHp;
}

bool Pokemon::tryStruggling(){
    if (!isStruggling) {
        if((move1->getCurrentPP()==0)&&(move2->getCurrentPP()==0)&&(move3->getCurrentPP()==0)&&(move4->getCurrentPP()==0))
        {
            delete move1;
            delete move2;
            delete move3;
            delete move4;
            move1 = new Move();
            move2 = new Move();
            move3 = new Move();
            move4 = new Move();
            isStruggling=1;
        }
    }
    return isStruggling;
}

int Pokemon::useMove(int moveNo)
{
    int result;
    
    switch (moveNo) {
        case 1:
            result = move1->useMove();
            break;
        case 2:
            result = move2->useMove();
            break;
        case 3:
            result = move3->useMove();
            break;
        case 4:
            result = move4->useMove();
            break;
    }
    
    return result;
    
}
