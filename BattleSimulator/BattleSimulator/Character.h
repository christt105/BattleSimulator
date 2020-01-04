#pragma once
#include <string>
#include <vector>
#include "Attack.h"

class Character
{
public:
	Character() {}
	Character(const int& b_attack, const int& sp_attack, const int& speed, const int& health);
	~Character();

	void Load(const char* file);

	std::string ToString() const;
	std::string MovementsToString() const;

	void Reset();

private:
	int LoadStat(const std::string& line, const char* stat);
	
public:
	std::string name;
	std::string path;
	// stats
	int b_attack		= -1;
	int b_precision		= -1;
	int sp_attack		= -1;
	int sp_precision	= -1;
	int speed			= -1;
	int health			= -1;
	int health_max		= -1;
	int mana			= -1;
	int mana_max		= -1;
	int mana_cost		= -1;

	int mana_recover	= 30;
	int potion_recover  = 5;

	std::vector<Attack*> movements;
};

