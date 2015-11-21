//
//  AttackCalculator.cpp
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-19.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#include "AttackCalculator.h"

//AttackCalculator
AttackCalculator::AttackCalculator()
{
    this->chart = new double*[18];
    for (int i=0; i<18; i++)
    {
        chart[i]=new double[18];
    }
    
    for(int i=0; i<18; i++)
    {
        for (int j=0; j<18; j++)
        {
            chart[i][j]=1;
        }
    }
    //Attack if left def is right
    //Normal
    chart[0][5]=0.5;
    chart[0][7]=0;
    chart[0][8]=0.5;
    //Fighting
    chart[1][0]=2;
    chart[1][2]=0.5;
    chart[1][3]=0.5;
    chart[1][5]=2;
    chart[1][6]=0.5;
    chart[1][7]=0;
    chart[1][8]=2;
    chart[1][13]=0.5;
    chart[1][14]=2;
    chart[1][16]=2;
    chart[1][17]=0.5;
    //Flying
    chart[2][1]=2;
    chart[2][5]=0.5;
    chart[2][6]=2;
    chart[2][8]=0.5;
    chart[2][11]=2;
    chart[2][12]=0.5;
    //Poison
    chart[3][3]=0.5;
    chart[3][4]=0.5;
    chart[3][5]=0.5;
    chart[3][7]=0.5;
    chart[3][8]=0;
    chart[3][11]=2;
    chart[3][17]=2;
    //Ground
    chart[4][2]=0;
    chart[4][3]=2;
    chart[4][5]=2;
    chart[4][6]=0.5;
    chart[4][8]=2;
    chart[4][9]=2;
    chart[4][11]=0.5;
    chart[4][12]=2;
    //Rock
    chart[5][1]=0.5;
    chart[5][2]=2;
    chart[5][4]=0.5;
    chart[5][6]=2;
    chart[5][8]=0.5;
    chart[5][9]=2;
    chart[5][14]=2;
    //Bug
    chart[6][1]=0.5;
    chart[6][2]=0.5;
    chart[6][3]=0.5;
    chart[6][7]=0.5;
    chart[6][8]=0.5;
    chart[6][9]=0.5;
    chart[6][11]=2;
    chart[6][13]=2;
    chart[6][16]=2;
    chart[6][17]=0.5;
    //Ghost
    chart[7][0]=0;
    chart[7][7]=2;
    chart[7][13]=2;
    chart[7][16]=0.5;
    //Steel
    chart[8][5]=2;
    chart[8][8]=0.5;
    chart[8][9]=0.5;
    chart[8][10]=0.5;
    chart[8][12]=0.5;
    chart[8][14]=2;
    chart[8][17]=2;
    //Fire
    chart[9][5]=0.5;
    chart[9][6]=2;
    chart[9][8]=2;
    chart[9][9]=0.5;
    chart[9][10]=0.5;
    chart[9][11]=2;
    chart[9][14]=2;
    chart[9][15]=0.5;
    //Water
    chart[10][4]=2;
    chart[10][5]=2;
    chart[10][9]=2;
    chart[10][10]=0.5;
    chart[10][11]=0.5;
    chart[10][15]=0.5;
    //Grass
    chart[11][2]=0.5;
    chart[11][3]=0.5;
    chart[11][4]=2;
    chart[11][5]=2;
    chart[11][6]=0.5;
    chart[11][8]=0.5;
    chart[11][9]=0.5;
    chart[11][10]=2;
    chart[11][11]=0.5;
    chart[11][15]=0.5;
    //Electric
    chart[12][2]=2;
    chart[12][4]=0;
    chart[12][10]=2;
    chart[12][11]=0.5;
    chart[12][12]=0.5;
    chart[12][15]=0.5;
    //Psychic
    chart[13][1]=2;
    chart[13][3]=2;
    chart[13][8]=0.5;
    chart[13][13]=0.5;
    chart[13][16]=0;
    //Ice
    chart[14][2]=2;
    chart[14][4]=2;
    chart[14][8]=0.5;
    chart[14][9]=0.5;
    chart[14][10]=0.5;
    chart[14][11]=2;
    chart[14][14]=0.5;
    chart[14][15]=2;
    //Dragon
    chart[15][8]=0.5;
    chart[15][15]=2;
    chart[15][17]=0;
    //Dark
    chart[16][1]=0.5;
    chart[16][7]=2;
    chart[16][13]=2;
    chart[16][16]=0.5;
    chart[16][17]=0.5;
    //Fairy
    chart[17][1]=2;
    chart[17][3]=0.5;
    chart[17][8]=0.5;
    chart[17][9]=0.5;
    chart[17][15]=2;
    chart[17][16]=2;
};

AttackCalculator::~AttackCalculator()
{
    for (int i=0; i<18; i++)
    {
        delete chart[i];
    }
    delete chart;
};

int AttackCalculator::attackResultTranslator(std::vector<std::string>* resultHolder, std::string resultString, Pokemon* attacker, Pokemon* defender, int* usedMoveIndex)
{
    //Returns 8 character string. Last char 0=no effect 1=miss 2=not very 3=normal 4=super effect
    //Stats effected +10 if att 20 def 30 spatt 40-spdef 50-speed 60-eva 70-acc
    //+100 if stat change +200 sharply change for defender, 300 400 for attacker
    
    //+1000 if crit
    //10000s digit is the attack Number
    //1st char is direction of stat change n=none u=up d=down
    //2nd is status defender gets this turn n=none b=burn f=frozen p=paralyze a=poison s=sleeping c=confused
    //3rd is status already had same letters as above plus P=paralyzed but attack works F=thaw S=woke up C=confused but attack works 0=snap out of confusion
    //Example unb21324 means a supereffective attack that raised attackers defence one stage, was a critical hit, was their 2nd of their 4 attacks, and they are suffering from a burn.

    
    std::vector<std::string> parsedStrings;
    std::stringstream ss(resultString);
    
    std::string tempChar="";
    char i;
    
    while(ss>>i)
    {
        tempChar+=i;
        parsedStrings.push_back(tempChar);
        tempChar="";
    }
    
    std::string directStatus = parsedStrings.at(0);
    std::string newStatus = parsedStrings.at(1);
    std::string currentStatus = parsedStrings.at(2);
    int attackNo = std::stoi(parsedStrings.at(3));
    int crit = std::stoi(parsedStrings.at(4));
    int statJump = std::stoi(parsedStrings.at(5));
    int statEffed = std::stoi(parsedStrings.at(6));
    int effective = std::stoi(parsedStrings.at(7));
    
    int phraseCount=0;
    std::string temp="";
    
    //Attack phrase
    //int posResult = abs(result);
    //int attackNo = posResult/1000000;
    //int nowStatis = (posResult-(attackNo*1000000))/100000;
    //int attackNo = posResult/10000;
    //int crit = (posResult-(attackNo*10000))/1000;
    //int statJump = ((posResult-(attackNo*10000))-crit*1000)/100;
    //int statEffed = (((posResult-(attackNo*10000))-crit*1000)-(statJump*100))/10;
    //int effective = ((((posResult-(attackNo*10000))-crit*1000)-(statJump*100))-(statEffed*10));
    
    //Currently under status of sleep confuse para freeze
    if(currentStatus=="f")
    {
        resultHolder->push_back(attacker->getName()+" is frozen solid!");
        phraseCount++;
    }
    else if(currentStatus=="F")
    {
        resultHolder->push_back(attacker->getName()+" thawed out!");
        phraseCount++;
    }
    else if(currentStatus=="p"||currentStatus=="P")
    {
        resultHolder->push_back(attacker->getName()+" is paralyzed!");
        phraseCount++;
        if(currentStatus=="p")
        {
            resultHolder->push_back(attacker->getName()+" is fully paralyzed!");
            phraseCount++;
        }
    }
    else if(currentStatus=="s")
    {
        resultHolder->push_back(attacker->getName()+" is fast asleep!");
        phraseCount++;
    }
    else if(currentStatus=="S")
    {
        resultHolder->push_back(attacker->getName()+" woke up!");
        phraseCount++;
    }
    else if(currentStatus=="c"||currentStatus=="C")
    {
        resultHolder->push_back(attacker->getName()+" is confused!");
        phraseCount++;
        if(currentStatus=="c")
        {
            resultHolder->push_back(attacker->getName()+" hurt itself in its confusion!");
            phraseCount++;
        }
        
    }
    else if(currentStatus=="o")
    {
        resultHolder->push_back(attacker->getName()+" snaped out of confusion!");
        phraseCount++;
    }
   
    
    if(currentStatus!="f"&&currentStatus!="s"&&currentStatus!="p"&&currentStatus!="c")
    {
        temp=attacker->getName()+" used ";
        temp=temp+attacker->getMove(attackNo)->getName()+"!";
        resultHolder->push_back(temp);
        *usedMoveIndex=phraseCount;
        phraseCount++;
        temp="";
    }
    
    
    
    //Crit phrase
    
    if (crit==1) {
        resultHolder->push_back("Critical hit!");
        phraseCount++;
    }
    
    
    
    //Effectiveness phrase
    
    switch (effective) {
        case 0:
            temp="It had no effect on "+defender->getName()+"...";
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 1:
            temp=attacker->getName()+"'s attack missed!";
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 2:
            temp="It's not very effective...";
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 4:
            temp="It's super effective!";
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        default:
            break;
    }
    
       
    
    
    //Stat changes
    std::string direction = " rose!";
    std::string effectedName = defender->getName()+"'s";
    std::string twoStages="";
    if(directStatus=="d")
    {
        direction=" fell!";
    }
    if (statJump>=3) {
        effectedName = attacker->getName()+"'s";
    }
    if (statJump==2||statJump==4) {
        if(directStatus=="d")
        {
        twoStages=" harshly";
        }
        else
        {
            twoStages=" sharply";
        }
    }
    
    
    
    switch (statEffed) {
        case 1:
            temp=effectedName+" attack"+twoStages+direction;
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 2:
            temp=effectedName+" defense"+twoStages+direction;
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 3:
            temp=effectedName+" special attack"+twoStages+direction;
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 4:
            temp=effectedName+" special defense"+twoStages+direction;
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 5:
            temp=effectedName+" speed"+twoStages+direction;
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 6:
            temp=effectedName+" evasion"+twoStages+direction;
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
        case 7:
            temp=effectedName+" accuracy"+twoStages+direction;
            resultHolder->push_back(temp);
            phraseCount++;
            temp="";
            break;
            
        default:
            break;
    }
    
    //Statis effect applyed to defender
    if(newStatus=="b")
    {
        resultHolder->push_back(defender->getName()+" was burned!");
        phraseCount++;
    }
    else if(newStatus=="f")
    {
        resultHolder->push_back(defender->getName()+" was frozen solid!");
        phraseCount++;
    }
    else if(newStatus=="p")
    {
        resultHolder->push_back(defender->getName()+" became paralyzed!");
        phraseCount++;
    }
    else if(newStatus=="a")
    {
        resultHolder->push_back(defender->getName()+" was poisoned!");
        phraseCount++;
    }
    else if(newStatus=="s")
    {
        resultHolder->push_back(defender->getName()+" fell asleep!");
        phraseCount++;
    }
    else if(newStatus=="c")
    {
        resultHolder->push_back(defender->getName()+" became confused!");
        phraseCount++;
    }

    
    if(currentStatus=="b")
    {
        resultHolder->push_back(attacker->getName()+" turn damage from burn!");
        phraseCount++;
    }
    else if(currentStatus=="a")
    {
        resultHolder->push_back(defender->getName()+" was hurt from poison!");
        phraseCount++;
    }
    
    return phraseCount;
}

int AttackCalculator::typeTranslator(std::string type)
{
    if(type=="Normal")
    {
        return 0;
    }
    else if(type=="Fighting")
    {
        return 1;
    }
    else if(type=="Flying")
    {
        return 2;
    }
    else if(type=="Poison")
    {
        return 3;
    }
    else if(type=="Ground")
    {
        return 4;
    }
    else if(type=="Rock")
    {
        return 5;
    }
    else if(type=="Bug")
    {
        return 6;
    }
    else if(type=="Ghost")
    {
        return 7;
    }
    else if(type=="Steel")
    {
        return 8;
    }
    else if(type=="Fire")
    {
        return 9;
    }
    else if(type=="Water")
    {
        return 10;
    }
    else if(type=="Grass")
    {
        return 11;
    }
    else if(type=="Electric")
    {
        return 12;
    }
    else if(type=="Psychic")
    {
        return 13;
    }
    else if(type=="Ice")
    {
        return 14;
    }
    else if(type=="Dragon")
    {
        return 15;
    }
    else if(type=="Dark")
    {
        return 16;
    }
    else if(type=="Fairy")
    {
        return 17;
    }
    
    
    return -1;

};

double AttackCalculator::calcMultiplier(std::string attack, std::string def1, std::string def2)
{
    double multiplier=1;
    int attackInt = typeTranslator(attack);
    int def1Int = typeTranslator(def1);
    int def2Int;
    bool twoType = false;
    if(def2!="NULL")
    {
        def2Int = typeTranslator(def2);
        twoType = true;
    }
    
    multiplier*=chart[attackInt][def1Int];
    
    if(twoType)
    {
        multiplier*=chart[attackInt][def2Int];
    }
    
    return multiplier;
};

bool AttackCalculator::effectedByStatis(Pokemon* attacker, int* result, std::string* statusOld)
{
    int statis = attacker->getCurrentStatis();
    bool skipRest = false;
    
    switch (statis) {
        case 1:
            attacker->dealDamage(attacker->getMaxHP()/8);
            *statusOld="b";
            break;
        case 2:
        {
            int iceChance = rand()%100;
            if (iceChance<20) {
                *statusOld="F";
                attacker->setCurrentStatis(0);
            }
            else{
                *statusOld="f";
                skipRest=true;
            }
            break;
        }
        case 3:
        {
            int paraChance = rand()%100;
            if (paraChance<25) {
                skipRest=true;
                *statusOld="p";
            }
            else{
            *statusOld="P";
            }
            break;
        }
        case 4:
            attacker->dealDamage(attacker->getMaxHP()/16);
            *statusOld="a";
            break;
        case 5:
            attacker->setCurrentStatis(6);
            skipRest=true;
            *statusOld="s";
            break;
        case 6:
        {
            int sleepChance = rand()%100;
            if (sleepChance<33) {
                *statusOld="S";
                attacker->setCurrentStatis(0);
            }
            else{
                *result=*result+60000;
                skipRest=true;
                *statusOld="s";
            }
            break;
        }
        case 7:
        {
            attacker->setCurrentStatis(8);
            int confChance = rand()%2;
            if(confChance==0)
            {
                attacker->dealDamage((int) ((110.0/250.0)*((attacker->getAtt()/attacker->getDef()))*40)*(((85+(rand()%15))/100.0)));
                skipRest=true;
                *statusOld="c";
            }
            
            *statusOld="C";
            break;
        }
        case 8:
        {
            int confChance2 = rand()%100;
            int confChance3 = rand()%2;
            if (confChance2<25) {
                attacker->setCurrentStatis(0);
                *statusOld="o";
            }
            else if (confChance3==0) {
                attacker->dealDamage((int) ((110.0/250.0)*((attacker->getAtt()/attacker->getDef()))*40)*(((85+(rand()%15))/100.0)));
                skipRest=true;
                *statusOld="c";
            }
            else{
                *statusOld="C";
            }
            break;
        }
            
        default:
            break;
    }
    
    return skipRest;
}

std::string AttackCalculator::applyDamage(Pokemon* attacker, Pokemon* defender, int attackNo)
{
    
    Move *usedMove = attacker->getMove(attackNo);
    int result=3;
    std::string statusNew = "n";
    std::string statusOld = "n";
    std::string statusDirect = "n";
    if(usedMove->getStatChange()<0)
    {
        statusDirect = "d";
    }
    else if(usedMove->getStatChange()>0)
    {
        statusDirect = "u";
    }
    std::string resultString = "";
    
    //Check if effected by statis
    bool skipRest = effectedByStatis(attacker, &result, &statusOld);
    
    if (skipRest) {
        result=result+(attackNo*10000);
        resultString = statusNew + statusOld + std::to_string(result);
        return resultString;
    }
    
    //See if hit or miss
    double percentage=1;
    if(usedMove->getAccuracy()!=0)
    {
        percentage = ((usedMove->getAccuracy())/100.0)*((attacker->getAccuracy())/(defender->getEvasion()));
    }
    
    if(percentage<1)//Attack missed
    {
        result=1;
        result=result+(attackNo*10000);
        resultString = statusNew + statusOld + std::to_string(result);
        return resultString;
    }
    
    //Calculate the multiplyer for the attack
    double multiplier = calcMultiplier(usedMove->getType(), defender->getType1(), defender->getType2());
    if (multiplier==0) {
        result=result+(attackNo*10000);
        resultString = statusNew + statusOld + std::to_string(result);
        return resultString;
    }
    else if(multiplier<1)
    {
        result=2;
    }
    else if(multiplier==1)
    {
        result=3;
    }
    else
    {
        result=4;
    }
    
    float STAB=1;//Same type attack bonus
    if(usedMove->getType()==attacker->getType1()||usedMove->getType()==attacker->getType2())
    {
        STAB=1.5;
    }
    
    float crit=1;//Check for a critical hit
    if(usedMove->getAccuracy()!=0)
    {
        if(rand()%16==15)
        {
            crit=1.5;
        }
    }
    int damage=0;
    
    //Calculated the amount of HP damage done by the attack. If has no power avoids unneed calcs
    if(usedMove->getPower()!=0)
    {
    if(usedMove->getPhysOrSpec())
    {
        damage = (int) ((110.0/250.0)*((attacker->getAtt()/defender->getDef()))*usedMove->getPower())*(STAB*multiplier*crit*((85+(rand()%15))/100.0));
    }
    else
    {
        damage = (int) ((110.0/250.0)*((attacker->getSpAtt()/defender->getSpDef()))*usedMove->getPower())*(STAB*multiplier*crit*((85+(rand()%15))/100.0));
    }
    }
    else
    {
        result=3;
    }
    
    if (crit==1.5)
    {
        result+=1000;
    }
    
    //Actually apply the damage
    defender->dealDamage(damage);
    
    //Secondary Effects
    if(usedMove->getStatChange()!=0)
    {
        int chance=usedMove->getChangeChance();
        int randNum = rand()%100;
        
        if(randNum<chance)
        {
            if (usedMove->getStatUser())
            {
                defender->changeStages(usedMove, &result, &statusNew, 1);
            }
            else
            {
                attacker->changeStages(usedMove, &result, &statusNew, 2);
            }
        }
    }
    
    result=result+(attackNo*10000);
    resultString = statusDirect + statusNew + statusOld + std::to_string(result);
    return resultString;
}