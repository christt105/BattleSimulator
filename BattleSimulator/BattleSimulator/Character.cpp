#include "Character.h"
#include <fstream>
#include <iostream>

Character::Character(const int & attack, const int & defense, const int & speed, const int & health)
	: attack(attack), defense(defense), speed(speed), health(health)
{
}

Character::~Character()
{
	for (auto i = movements.begin(); i != movements.end(); i++)
		delete *i;
}

void Character::Load(const char * file)
{
	//TODO: reset character
	std::ifstream f(file);
	if (f.is_open()) {
		std::string line;
		while (std::getline(f, line))
		{
			if (line.find("name:") != std::string::npos) {
				auto c = line.begin() + line.find("name:") + strlen("name:");
				//find first char
				while (!isalpha(*c) && *c != '\n') {
					c++;
				}
				//set name
				name.clear();
				while (c != line.end()) {
					name += *c;
					c++;
				}
			}
			else if (line.find("speed:") != std::string::npos) {
				speed = LoadStat(line, "speed:");
			}
			else if (line.find("damage:") != std::string::npos) {
				attack = LoadStat(line, "damage:");
			}
			else if (line.find("defense:") != std::string::npos) {
				defense = LoadStat(line, "defense:");
			}
			else if (line.find("health:") != std::string::npos) {
				health = LoadStat(line, "health:");
			}
			//TODO: Load Movements
		}
		f.close();
	}

	movements.push_back(new Tackle());
}

std::string Character::MovementsToString() const
{
	std::string ret;
	int n = 0;
	for (auto i = movements.begin(); i != movements.end(); i++) {
		ret.append("(" + std::to_string(n) + ")" + (*i)->name + '\n');
	}
	return ret;
}

std::string Character::ToString() const
{
	return std::string(
		name + '\n' +
		"attack: " + std::to_string(attack) + '\n' + 
		"defense: " + std::to_string(defense) + '\n' + 
		"speed: " + std::to_string(speed) + '\n' + 
		"health: " + std::to_string(health)
	);
}

int Character::LoadStat(const std::string & line, const char * stat)
{
	auto c = line.begin() + line.find(stat) + strlen(stat);
	//find first char
	while (!isdigit(*c) && *c != '\n') {
		c++;
	}
	//find last entire number
	std::string num;
	while (c != line.end() && isdigit(*c)) {
		num += *c;
		c++;
	}

	return std::atoi(num.c_str());
}
