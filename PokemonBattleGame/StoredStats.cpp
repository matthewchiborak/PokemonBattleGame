//
//  StoredStats.cpp
//  TypeChart
//
//  Created by Matthew Chiborak on 2015-11-20.
//  Copyright (c) 2015 Matthew Chiborak. All rights reserved.
//

#include "StoredStats.h"

StoredStats::StoredStats(std::string statString)
{
	std::vector<std::string> parsedStrings;
	std::stringstream ss(statString);
	std::string temp = "";
	char i;

	while (ss >> i)
	{
		temp += i;

		if (ss.peek() == ',')
		{
			ss.ignore();
			parsedStrings.push_back(temp);
			temp = "";
		}
	}
	parsedStrings.push_back(temp);

	ID = std::stoi(parsedStrings.at(0));
	name = parsedStrings.at(1);
	type1 = parsedStrings.at(2);
	type2 = parsedStrings.at(3);
	maxhp = std::stoi(parsedStrings.at(5));
	minhp = std::stoi(parsedStrings.at(4));
	maxAtt = std::stoi(parsedStrings.at(7));
	minAtt = std::stoi(parsedStrings.at(6));
	maxSpAtt = std::stoi(parsedStrings.at(9));
	minSpAtt = std::stoi(parsedStrings.at(8));
	maxDef = std::stoi(parsedStrings.at(11));
	minDef = std::stoi(parsedStrings.at(10));
	maxSpDef = std::stoi(parsedStrings.at(13));
	minSpDef = std::stoi(parsedStrings.at(12));
	maxSpeed = std::stoi(parsedStrings.at(15));
	minSpeed = std::stoi(parsedStrings.at(14));
	move1 = std::stoi(parsedStrings.at(16));
	move2 = std::stoi(parsedStrings.at(17));
	move3 = std::stoi(parsedStrings.at(18));
	move4 = std::stoi(parsedStrings.at(19));
}

int StoredStats::getID() {
	return ID;
}
std::string StoredStats::getName() {
	return name;
}
std::string StoredStats::getType1() {
	return type1;
}
std::string StoredStats::getType2() {
	return type2;
}
int StoredStats::getMaxhp() {
	return maxhp;
}
int StoredStats::getMinhp() {
	return minhp;
}
int StoredStats::getMaxAtt() {
	return maxAtt;
}
int StoredStats::getMinAtt() {
	return minAtt;
}
int StoredStats::getMaxSpAtt() {
	return maxSpAtt;
}
int StoredStats::getMinSpAtt() {
	return minSpAtt;
}
int StoredStats::getMaxDef() {
	return maxDef;
}
int StoredStats::getMinDef() {
	return minDef;
}
int StoredStats::getMaxSpDef() {
	return maxSpDef;
}
int StoredStats::getMinSpDef() {
	return minSpDef;
}
int StoredStats::getMaxSpeed() {
	return maxSpeed;
}
int StoredStats::getMinSpeed() {
	return minSpeed;
}

int StoredStats::getMove1()
{
	return move1;
}
int StoredStats::getMove2()
{
	return move2;
}
int StoredStats::getMove3()
{
	return move3;
}
int StoredStats::getMove4()
{
	return move4;
}