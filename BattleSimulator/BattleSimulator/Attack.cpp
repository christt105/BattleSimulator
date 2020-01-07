#include <iostream>
#include "Attack.h"
#include "Character.h"
#include "Game.h"
#include "Audio.h"

std::string Attack::ToString() const
{
	return std::string();
}

bool Basic::DoAttack(Character * attacker, Character * objective)
{
	int r_precision = rand() % 100 + 1;
	if (r_precision <= attacker->b_precision) { //precision
		objective->health -= attacker->b_attack;
		game->audio->PlayFX("Adventure/Audio/tackle.mp3");
		return true;
	}
	std::cout << attacker->name << " failed basic attack" << std::endl;
	return false;
}

bool Special::DoAttack(Character * attacker, Character * objective)
{
	if (attacker->mana - attacker->mana_cost >= 0) {
		attacker->mana -= attacker->mana_cost;
		objective->health -= attacker->sp_attack;
		return true;
	}
	else {
		std::cout << attacker->name << " failed special attack, not enough mana" << std::endl;
	}
	return false;
}

bool Reload::DoAttack(Character * attacker, Character * objective)
{
	if (attacker->mana + attacker->mana_recover >= attacker->mana_max) {
		attacker->mana = attacker->mana_max;
	}
	else {
		attacker->mana += attacker->mana_recover;
	}

	return true;
}

bool Dodge::DoAttack(Character * attacker, Character * objective)
{
	attacker->n_parry--;
	return true;
}

bool Potion::DoAttack(Character * attacker, Character * objective)
{
	if (attacker->health + attacker->potion_recover >= attacker->health_max) {
		attacker->health = attacker->health_max;
	}
	else {
		attacker->health += attacker->potion_recover;
	}
	attacker->n_potions--;

	return true;
}
