#include "Battle.h"
#include "Game.h"
#include <iostream>


Battle::Battle()
{
}


Battle::~Battle()
{
}

void Battle::DoBattle(const Character & character1, const Character & character2, Game::PlayMode mode)
{
	characters[0] = character1;
	characters[1] = character2;
	this->mode = mode;

	int turn = 1;
	while (DoTurn(turn++)) { }

	int ch_wins = (characters[0].health > 0) ? 0 : 1;

	std::cout << "Character " << ch_wins << " (" << characters[ch_wins].name << ") won" << std::endl;

	getchar();
	system("pause");
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
		DoAIvAITurn();
		break;
	case Game::PlayMode::AIvsAI:
		DoAIvAITurn();
		break;
	default:
		break;
	}

	return AreCharactersAlive();
}

void Battle::DoHvHTurn()
{
	std::cout << characters[0].name << " select attack:" << std::endl;
	std::cout << characters[0].MovementsToString() << std::endl;

	int result = -1;
	while (!(std::cin >> result) || result < 0 || result > characters[0].movements.size()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << characters[0].name << " uses " << characters[0].movements[result]->name << std::endl;
	characters[0].movements[result]->DoAttack(&characters[0], &characters[1]);
}

void Battle::DoHvAITurn()
{
}

void Battle::DoAIvAITurn()
{
}
