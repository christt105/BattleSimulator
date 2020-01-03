#include "Attack.h"
#include "Character.h"

std::string Attack::ToString() const
{
	return std::string();
}

void Tackle::DoAttack(Character * attacker, Character * objective)
{
	objective->health -= attacker->attack;
}
