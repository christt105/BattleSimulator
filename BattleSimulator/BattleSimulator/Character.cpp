#include "Character.h"

Character::Character(const int & attack, const int & defense, const int & speed, const int & life)
	: attack(attack), defense(defense), speed(speed), life(life)
{
}

Character::~Character()
{
}

std::string Character::ToString()
{
	return std::string(
		"attack: " + std::to_string(attack) + " | " + 
		"defense: " + std::to_string(defense) + " | " + 
		"speed: " + std::to_string(speed) + " | " + 
		"life: " + std::to_string(life)
	);
}
