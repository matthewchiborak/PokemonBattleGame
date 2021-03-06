//
//  Pokemon.h
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-19.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#ifndef __TypeChart__Pokemon__
#define __TypeChart__Pokemon__

#include <iostream>
#include "Move.h"
#include <vector>
#include "StoredStats.h"
#include <sstream>

class Pokemon
{
private:
    int ID;
    std::string name;
    std::string type1;
    std::string type2;
    int hp;
    int maxHp;
    double att;
    double spAtt;
    double def;
    double spDef;
    int speed;
    double evasion;
    double accuarcy;
	double attStart;
	double spAttStart;
	double defStart;
	double spDefStart;
	int speedStart;
	double evasionStart;
	double accuarcyStart;
    Move* move1;
    Move* move2;
    Move* move3;
    Move* move4;
    int currentStatis;
    bool isStruggling;
    int previousTurnHp;
    
    
public:
    Pokemon(StoredStats *pkmnInfo, std::vector<std::string> *moveInfo); //For creating your own Pokemon
    Pokemon(std::vector<std::string> *moveInfo, std::string stats);//For creating opponents Pokemon
	Pokemon(StoredStats *pkmnInfo);//Temp while moves have not been implemneted
    ~Pokemon();
    std::string sendCreationStats();
    void updateStats(std::string stats);
    std::string getNewStats();
    Move* getMove(int num);
    std::string getType1();
    std::string getType2();
    double getEvasion();
    double getAccuracy();
    double getAtt();
    double getDef();
    double getSpAtt();
    double getSpDef();
    void dealDamage(int damage); //Used by AttackCalculator
    int getHP();
    int getMaxHP();
    void changeStages(Move* usedMove, int* result, std::string* newStatus, int aOrD); //Used by Attack Calculator. A is (1 multiply)attacker D is defender (x2)
    int getSpeed();
    int getID();
    std::string getName();
    int getCurrentStatis();
    void setCurrentStatis(int statis);
    void removeConfusion();
    int useMove(int moveNo);
    bool tryStruggling();
    int getPreviousTurnHp();
};


#endif /* defined(__TypeChart__Pokemon__) */
