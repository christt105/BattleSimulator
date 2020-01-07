#include "Character.h"
#include "ConsoleColor.h"
#include <fstream>
#include <iostream>

Character::Character(const int & b_attack, const int & sp_attack, const int & speed, const int & health)
	: b_attack(b_attack), sp_attack(sp_attack), speed(speed), health(health)
{
}

Character::~Character()
{
	for (auto i = movements.begin(); i != movements.end(); i++)
		delete *i;
}

void Character::Load(const char * file)
{
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
			else if (line.find("basic_attack:") != std::string::npos) {
				b_attack = LoadStat(line, "basic_attack:");
			}
			else if (line.find("b_precision:") != std::string::npos) {
				b_precision = LoadStat(line, "b_precision:");
			}
			else if (line.find("special_attack:") != std::string::npos) {
				sp_attack = LoadStat(line, "special_attack:");
			}
			else if (line.find("sp_precision:") != std::string::npos) {
				sp_precision = LoadStat(line, "sp_precision:");
			}
			else if (line.find("health:") != std::string::npos) {
				health_max = health = LoadStat(line, "health:");
			}
			else if (line.find("mana:") != std::string::npos) {
				mana_max = mana = LoadStat(line, "mana:");
			}
			else if (line.find("mana_cost:") != std::string::npos) {
				mana_cost = LoadStat(line, "mana_cost:");
			}
			else if (line.find("potions:") != std::string::npos) {
				start_potions = n_potions = LoadStat(line, "potions:");
			}
		}
		f.close();
		if (movements.empty()) {
			movements.push_back(new Basic());
			movements.push_back(new Special());
			movements.push_back(new Reload());
			movements.push_back(new Dodge());
			movements.push_back(new Potion());
		}
	}
}

std::string Character::MovementsToString() const
{
	std::string ret;
	int n = 0;
	for (auto i = movements.begin(); i != movements.end(); i++) {
		ret.append("(" + std::to_string(n) + ") " + (*i)->name + '\n');
		n++;
	}
	return ret;
}

void Character::Reset()
{
	health = health_max;
	mana = mana_max;
	n_parry = n_max_parry;
	n_potions = start_potions;
}

void Character::PrintStats() const
{
	std::cout << name << std::endl;
	if (health <= health_max * 0.5f) {
		if (health <= health_max * 0.25f) {
			std::cout << red;
		}
		else {
			std::cout << yellow;
		}
	}
	std::cout << "health: " << health << '/' << health_max << white << std::endl
		<< "basic attack: " << b_attack << " precision: " << b_precision << std::endl;
	if (mana - mana_cost < 0) {
		std::cout << red;
	}
	std::cout << "special attack: " << sp_attack << " precision: " << sp_precision << " cost: " << mana_cost << white << std::endl;
	if (mana <= mana_max * 0.5f) {
		if (mana <= mana_max * 0.25f) {
			std::cout << red;
		}
		else {
			std::cout << yellow;
		}
	}
	std::cout << "mana: " << mana << '/' << mana_max << white << std::endl;
	if (n_potions <= 0)
		std::cout << red;
	std::cout << "potions: " << n_potions << white << std::endl;
	if (n_parry <= 0)
		std::cout << red;
	std::cout << "parrys: " << n_parry << white << std::endl
		<< "speed: " << speed << std::endl;
}

std::string Character::ToString() const
{
	return std::string(
		name + '\n' +
		"health: " + std::to_string(health) + '/' + std::to_string(health_max) + '\n' +
		"b_attack: " + std::to_string(b_attack) + " precision: " + std::to_string(b_precision) + '\n' +
		"sp_attack: " + std::to_string(sp_attack) + " precision: " + std::to_string(sp_precision) + " cost: " + std::to_string(mana_cost) + '\n' +
		"mana: " + std::to_string(mana) + '/' + std::to_string(mana_max) + '\n' +
		"potions: " + std::to_string(n_potions) + '\n' +
		"parrys: " + std::to_string(n_parry) + '\n' +
		"speed: " + std::to_string(speed) + '\n'
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
