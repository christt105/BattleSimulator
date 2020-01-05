#include "Battle.h"
#include "Game.h"
#include <iostream>


Battle::Battle()
{
}


Battle::~Battle()
{
}

bool Battle::DoBattle(const Character & character1, const Character & character2, Game::PlayMode mode)
{
	characters[0] = character1;
	characters[1] = character2;
	this->mode = mode;

	if (mode == Game::PlayMode::TEST_ONE_MOV) {
		std::cout << "Select a movement you want to test:" << std::endl;
		std::cout << characters[0].MovementsToString() << std::endl;

		while (!(std::cin >> mov_test) || mov_test < 0 || mov_test > characters[0].movements.size()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << "How many times do you want to test:" << std::endl << std::endl;

		while (!(std::cin >> times_mov_test) || times_mov_test < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	if (mode != Game::PlayMode::TEST_HUNDRED_BATTLES  && mode != Game::PlayMode::TEST_ONE_MOV) {
		int turn = 1;
		while (DoTurn(turn++)) {}

		int ch_wins = (characters[0].health > 0) ? 0 : 1;


		if (mode == Game::PlayMode::ADVENTURE) {
			if (ch_wins != 0) {
				std::cout << "DEFEAT, restarting battle" << std::endl;
				return true;
			}
			else {
				std::cout << "Brodinski won" << std::endl;
			}
		}
		else {
			std::cout << "Character " << ch_wins << " (" << characters[ch_wins].name << ") won" << std::endl;
			int res;
			std::cout << std::endl << "(0) Restart battle" << std::endl << "(1) Return to Main Menu" << std::endl;

			while (!(std::cin >> res) || res < 0 || res > 1) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			if (res == 0) {
				return true;
			}
			else if (res == 1) {
				return false;
			}
		}
	}
	else {
		if (mode == Game::PlayMode::TEST_HUNDRED_BATTLES)
			times_mov_test = 100;

		int n_0_wins = 0;
		for (int i = 0; i < times_mov_test; i++) {
			int turn = 1;
			while (DoTurn(turn++)) {}
			if (characters[0].health > 0)
				n_0_wins++;
			characters[0].Reset();
			characters[1].Reset();
		}
		std::cout << std::endl << "Character 0 (" << characters[0].name << "): won " << n_0_wins << "/" << times_mov_test;
		std::cout << std::endl << "Character 1 (" << characters[1].name << "): won " << times_mov_test - n_0_wins << "/" << times_mov_test << std::endl << std::endl;
		system("pause");
	}
	return false;
}

bool Battle::AreCharactersAlive()
{
	return characters[0].health > 0 && characters[1].health > 0;
}

bool Battle::DoTurn(int n_turn)
{
	std::cout << "Turn number " << n_turn  << ", characters:" << std::endl << std::endl << characters[0].ToString() << std::endl << std::endl << characters[1].ToString() << std::endl << std::endl;

	switch (mode)
	{
	case Game::PlayMode::HvsH:
		DoHvHTurn();
		break;
	case Game::PlayMode::HvsAI:
	case Game::PlayMode::ADVENTURE:
		DoHvAITurn();
		break;
	case Game::PlayMode::AIvsAI:
	case Game::PlayMode::TEST_HUNDRED_BATTLES:
		DoAIvAITurn();
		break;
	case Game::PlayMode::TEST_ONE_MOV:
		TestMovementTurn();
		break;
	default:
		break;
	}

	return AreCharactersAlive();
}

void Battle::DoHvHTurn()
{
	int mov1, mov2;
	for (int ch = 0; ch < 2; ch++) {
		int result = -1;
		if (characters[ch].parried) {
			std::cout << "Player " << ch + 1 << " " << characters[ch].name << " got parried on last turn, cannot attack in this turn" << std::endl;
		}
		else if (characters[ch].parry) {
			std::cout << "Player " << ch + 1 << " " << characters[ch].name << " select a movement after have done parry:" << std::endl;
			std::cout << "(0) Basic" << std::endl;
			std::cout << "(1) Reload" << std::endl;
			std::cout << "(2) Potion" << std::endl;

			while (!(std::cin >> result) || result < 0 || result > 2) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			if (result == 1) //need to parse to normal attacks order
				result = 2;
			if (result == 2)
				result = 4;
		}
		else {
			std::cout << "Player " << ch + 1 << " " << characters[ch].name << " select a movement:" << std::endl;
			std::cout << characters[ch].MovementsToString() << std::endl;

			while (!(std::cin >> result) || result < 0 || result > characters[ch].movements.size() - 1 || (result == 1 && characters[ch].mana - characters[ch].mana_cost < 0)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (result == 1 && characters[ch].mana - characters[ch].mana_cost < 0)
					std::cout << "Cannot do Special, not enough mana" << std::endl;
			}
		}
		if (ch == 0) {
			mov1 = result;
		}
		else {
			mov2 = result;
		}
	}

	CalculateFirstAttacker(mov1, mov2);
}

void Battle::DoHvAITurn()
{
	int mov1 = -1;
	int mov2 = -1;

	//Player
	if (characters[0].parried) {
		std::cout << "Player " << characters[0].name << " got parried on last turn, cannot attack in this turn" << std::endl;
	}
	else if (characters[0].parry) {
		std::cout << "Player " << characters[0].name << " select a movement after have done parry:" << std::endl;
		std::cout << "(0) Basic" << std::endl;
		std::cout << "(1) Reload" << std::endl;
		std::cout << "(2) Potion" << std::endl;

		while (!(std::cin >> mov1) || mov1 < 0 || mov1 > 2) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (mov1 == 1) //need to parse to normal attacks order
			mov1 = 2;
		if (mov1 == 2)
			mov1 = 4;
	}
	else {
		std::cout << "Player " << characters[0].name << " select a movement:" << std::endl;
		std::cout << characters[0].MovementsToString() << std::endl;

		while (!(std::cin >> mov1) || mov1 < 0 || mov1 > characters[0].movements.size() - 1 || (mov1 == 1 && characters[0].mana - characters[0].mana_cost < 0)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (mov1 == 1 && characters[0].mana - characters[0].mana_cost < 0)
				std::cout << "Cannot do Special, not enough mana" << std::endl;
		}
	}
	//AI
	if (characters[1].parried) {
		std::cout << characters[1].name << " got parried on last turn, cannot attack in this turn" << std::endl;
	}
	else if (characters[1].parry) {
		mov2 = rand() % 3;

		if (mov2 == 1) //need to parse to normal attacks order
			mov2 = 2;
		if (mov2 == 2)
			mov2 = 4;
	}
	else {
		mov2 = AIThinkMov(1);
	}
	CalculateFirstAttacker(mov1, mov2);

	std::cout << std::endl;
}

void Battle::DoAIvAITurn()
{
	int mov1 = -1;
	int mov2 = -1;
	for (int i = 0; i < 2; i++) {
		if (characters[i].parried) {
			std::cout << characters[i].name << " got parried on last turn, cannot attack in this turn" << std::endl;
		}
		else if (characters[i].parry) {
			mov2 = rand() % 3;

			if (i == 0) {
				if (mov1 == 1) //need to parse to normal attacks order
					mov1 = 2;
				if (mov1 == 2)
					mov1 = 4;
			}
			else {
				if (mov2 == 1) //need to parse to normal attacks order
					mov2 = 2;
				if (mov2 == 2)
					mov2 = 4;
			}
		}
		else {
			if (i == 0)
				mov1 = AIThinkMov(0);
			else
				mov2 = AIThinkMov(1);
		}
	}

	CalculateFirstAttacker(mov1, mov2);

	std::cout << std::endl;
}

void Battle::TestMovementTurn()
{
	int mov1 = mov_test;
	if (mov_test == Attack::Type::SPECIAL && characters[0].mana - characters[0].mana_cost <= 0)
		mov1 = Attack::Type::RELOAD;
	int mov2 = AIThinkMov(1);

	if (characters[0].parried)
		mov1 = -1;
	else if (characters[0].parry)
		mov1 = 0;

	CalculateFirstAttacker(mov1, mov2);

	std::cout << std::endl;
}

void Battle::CalculateFirstAttacker(int mov1, int mov2)
{
	if (characters[0].speed > characters[1].speed) {
		DoAttacks(0, 1, mov1, mov2);
	}
	else if (characters[1].speed > characters[0].speed) {
		DoAttacks(1, 0, mov2, mov1);
	}
	else {
		int first = rand() % 2;

		if (first == 0) {
			DoAttacks(0, 1, mov1, mov2);
		}
		else {
			DoAttacks(1, 0, mov2, mov1);
		}
	}
}

void Battle::DoAttacks(int first_attacker, int second_attacker, int mov1, int mov2)
{
	if (mov1 == Attack::Type::DODGE && (mov2 == Attack::Type::BASIC || mov2 == Attack::Type::SPECIAL)) {
		std::cout << characters[first_attacker].name << " made a parry" << std::endl;
		characters[first_attacker].parry = true;
		characters[second_attacker].parried = true;
	}
	else if (mov2 == Attack::Type::DODGE && (mov1 == Attack::Type::BASIC || mov1 == Attack::Type::SPECIAL)) {
		std::cout << characters[second_attacker].name << " made a parry" << std::endl;
		characters[second_attacker].parry = true;
		characters[first_attacker].parried = true;
	}
	else {
		characters[first_attacker].parry	= false;
		characters[first_attacker].parried	= false;
		characters[second_attacker].parried = false;
		characters[second_attacker].parry	= false;

		if (mov1 != -1) {
			std::cout << characters[first_attacker].name << " uses " << characters[first_attacker].movements[mov1]->name << std::endl;
			characters[first_attacker].movements[mov1]->DoAttack(&characters[first_attacker], &characters[second_attacker]);
		}

		if (mov2 != -1) {
			std::cout << characters[second_attacker].name << " uses " << characters[second_attacker].movements[mov2]->name << std::endl;
			characters[second_attacker].movements[mov2]->DoAttack(&characters[second_attacker], &characters[first_attacker]);
		}
	}
}

int Battle::AIThinkMov(int charac)
{
	std::vector<Attack::Type> attacks;
	attacks.push_back(Attack::Type::BASIC);
	attacks.push_back(Attack::Type::BASIC); //Twice for more possibility to do a basic

	if (characters[charac].mana - characters[charac].mana_cost > 0) {
		attacks.push_back(Attack::Type::SPECIAL);
	}

	if (characters[charac].mana_max - characters[charac].mana < characters[charac].mana_max * 0.5f) {
		attacks.push_back(Attack::Type::RELOAD);
	}

	if (characters[charac].health_max - characters[charac].health < characters[charac].health_max * 0.5f) {
		attacks.push_back(Attack::Type::POTION);
	}

	return (int)attacks[rand() % attacks.size()];
}