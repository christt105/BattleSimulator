#pragma once
#include <string>
class Character
{
public:
	Character() {}
	Character(const int& attack, const int& defense, const int& speed, const int& life);
	~Character();

	void Load(const char* file);

	std::string ToString();

public:
	// stats
	int attack	= 0;
	int defense = 0;
	int speed	= 0;
	int life	= 0;
};

