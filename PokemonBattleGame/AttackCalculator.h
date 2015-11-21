//
//  AttackCalculator.h
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-19.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#ifndef __TypeChart__AttackCalculator__
#define __TypeChart__AttackCalculator__

#include <iostream>
#include "Pokemon.h"

class AttackCalculator
{
private:
    double **chart;
    
public:
    AttackCalculator();
    ~AttackCalculator();
    int typeTranslator(std::string type);
    double calcMultiplier(std::string attack, std::string def1, std::string def2);
    
    //Give it an string array and then result int from the applyDamage or from over the connection and will fill the vectory with the resultphrases, returns the number of phrases that were added
    int attackResultTranslator(std::vector<std::string>* resultHolder, std::string resultString, Pokemon* attacker, Pokemon* defender, int* usedMoveIndex);
    
    //Returns 8 character string. Last char 0=no effect 1=miss 2=not very 3=normal 4=super effect
    //Stats effected +10 if att 20 def 30 spatt 40-spdef 50-speed 60-eva 70-acc
    //+100 if stat change +200 sharply change for defender, 300 400 for attacker
    
    //+1000 if crit
    //10000s digit is the attack Number
    //1st char is direction of stat change n=none u=up d=down
    //2nd is status defender gets this turn n=none b=burn f=frozen p=paralyze a=poison s=sleeping c=confused
    //3rd is status already had same letters as above plus P=paralyzed but attack works F=thaw S=woke up C=confused but attack works 0=snap out of confusion
    //Example unb21324 means a supereffective attack that raised attackers defence one stage, was a critical hit, was their 2nd of their 4 attacks, and they are suffering from a burn. 
    std::string applyDamage(Pokemon* attacker, Pokemon* defender, int attackNo);
    bool effectedByStatis(Pokemon* attacker, int* result, std::string* statusOld);
};

#endif /* defined(__TypeChart__AttackCalculator__) */
