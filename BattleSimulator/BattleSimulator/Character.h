#pragma once
#include <string>
#include <vector>
#include "Attack.h"

class Character
{
public:
	Character() {}
	Character(const int& attack, const int& defense, const int& speed, const int& health);
	~Character();

	void Load(const char* file);

	std::string ToString() const;
	std::string MovementsToString() const;

private:
	int LoadStat(const std::string& line, const char* stat);

public:
	std::string name;
	std::string path;
	// stats
	int attack	= 0;
	int defense = 0;
	int speed	= 0;
	int health	= 0;

	std::vector<Attack*> movements;
};

