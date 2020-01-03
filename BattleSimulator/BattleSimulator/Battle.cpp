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
	}
	int turn = 1;
	while (DoTurn(turn++)) { }

	int ch_wins = (characters[0].health > 0) ? 0 : 1;

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
		DoHvAITurn();
		break;
	case Game::PlayMode::AIvsAI:
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
		std::cout << "Player " << ch + 1 << " " << characters[ch].name << " select a movement:" << std::endl;
		std::cout << characters[ch].MovementsToString() << std::endl;

		int result = -1;
		while (!(std::cin >> result) || result < 0 || result > characters[ch].movements.size() - 1) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (ch == 0) {
			mov1 = result;
		}
		else {
			mov2 = result;
		}
	}

	if (characters[0].speed > characters[1].speed) {
		std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
		characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);

		std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
		characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);
	}
	else if (characters[1].speed > characters[0].speed) {
		std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
		characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);

		std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
		characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);
	}
	else {
		int first = rand() % 2;

		if (first == 0) {
			std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
			characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);

			std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
			characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);
		}
		else {
			std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
			characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);

			std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
			characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);
		}
	}
}

void Battle::DoHvAITurn()
{
	std::cout << "Player " << characters[0].name << " select a movement:" << std::endl;
	std::cout << characters[0].MovementsToString() << std::endl;

	int result = -1;
	while (!(std::cin >> result) || result < 0 || result > characters[0].movements.size() - 1) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	int ai_mov = rand() % characters[1].movements.size();

	if (characters[0].speed > characters[1].speed) {
		std::cout << characters[0].name << " uses " << characters[0].movements[result]->name << std::endl;
		characters[0].movements[result]->DoAttack(&characters[0], &characters[1]);

		std::cout << characters[1].name << " uses " << characters[1].movements[ai_mov]->name << std::endl;
		characters[1].movements[ai_mov]->DoAttack(&characters[1], &characters[0]);
	}
	else if (characters[1].speed > characters[0].speed) {
		std::cout << characters[1].name << " uses " << characters[1].movements[ai_mov]->name << std::endl;
		characters[1].movements[ai_mov]->DoAttack(&characters[1], &characters[0]);

		std::cout << characters[0].name << " uses " << characters[0].movements[result]->name << std::endl;
		characters[0].movements[result]->DoAttack(&characters[0], &characters[1]);
	}
	else {
		int first = rand() % 2;

		if (first == 0) {
			std::cout << characters[0].name << " uses " << characters[0].movements[result]->name << std::endl;
			characters[0].movements[result]->DoAttack(&characters[0], &characters[1]);

			std::cout << characters[1].name << " uses " << characters[1].movements[ai_mov]->name << std::endl;
			characters[1].movements[ai_mov]->DoAttack(&characters[1], &characters[0]);
		}
		else {
			std::cout << characters[1].name << " uses " << characters[1].movements[ai_mov]->name << std::endl;
			characters[1].movements[ai_mov]->DoAttack(&characters[1], &characters[0]);

			std::cout << characters[0].name << " uses " << characters[0].movements[result]->name << std::endl;
			characters[0].movements[result]->DoAttack(&characters[0], &characters[1]);
		}
	}

	std::cout << std::endl;
}

void Battle::DoAIvAITurn()
{
	int mov1 = rand() % characters[0].movements.size();
	int mov2 = rand() % characters[1].movements.size();

	if (characters[0].speed > characters[1].speed) {
		std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
		characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);

		std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
		characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);
	}
	else if (characters[1].speed > characters[0].speed) {
		std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
		characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);

		std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
		characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);
	}
	else {
		int first = rand() % 2;

		if (first == 0) {
			std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
			characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);

			std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
			characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);
		}
		else {
			std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
			characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);

			std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
			characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);
		}
	}

	std::cout << std::endl;
}

void Battle::TestMovementTurn()
{
	int mov1 = mov_test;
	int mov2 = rand() % characters[1].movements.size();

	if (characters[0].speed > characters[1].speed) {
		std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
		characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);

		std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
		characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);
	}
	else if (characters[1].speed > characters[0].speed) {
		std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
		characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);

		std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
		characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);
	}
	else {
		int first = rand() % 2;

		if (first == 0) {
			std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
			characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);

			std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
			characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);
		}
		else {
			std::cout << characters[1].name << " uses " << characters[1].movements[mov2]->name << std::endl;
			characters[1].movements[mov2]->DoAttack(&characters[1], &characters[0]);

			std::cout << characters[0].name << " uses " << characters[0].movements[mov1]->name << std::endl;
			characters[0].movements[mov1]->DoAttack(&characters[0], &characters[1]);
		}
	}

	std::cout << std::endl;
}
