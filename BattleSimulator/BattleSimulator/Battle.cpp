#define NOMINMAX
#include "Battle.h"
#include "Game.h"
#include "ConsoleColor.h"


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

	if (mode == Game::PlayMode::TEST_ONE_MOV || mode == Game::PlayMode::TEST_STAT) {
		std::cout << "Select a movement you want to test:" << std::endl;
		std::cout << characters[0].MovementsToString() << std::endl;

		while (!(std::cin >> mov_test) || mov_test < 0 || mov_test > characters[0].movements.size()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (mode == Game::PlayMode::TEST_ONE_MOV) {
			std::cout << "How many times do you want to test:" << std::endl << std::endl;

			while (!(std::cin >> times_mov_test) || times_mov_test < 0) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}
	if (mode != Game::PlayMode::TEST_HUNDRED_BATTLES  && mode != Game::PlayMode::TEST_ONE_MOV && mode != Game::PlayMode::TEST_STAT) {
		int turn = 1;
		while (DoTurn(turn++)) {}

		int ch_wins = (characters[0].health > 0) ? 0 : 1;


		if (mode == Game::PlayMode::ADVENTURE) {
			if (ch_wins != 0) {
				std::cout << red << "DEFEAT, restarting battle" << white << std::endl;
				return true;
			}
			else {
				std::cout << yellow << "Brodinski won" << white << std::endl;
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
		if (mode == Game::PlayMode::TEST_HUNDRED_BATTLES || mode == Game::PlayMode::TEST_STAT)
			times_mov_test = 100;

		int n_0_wins = 0;
		if (mode == Game::PlayMode::TEST_STAT) {
			int def_stat = -1;
			switch (mov_test)
			{
			case Attack::Type::BASIC:
				def_stat = characters[0].b_attack;
				break;
			case Attack::Type::SPECIAL:
				def_stat = characters[0].sp_attack;
				break;
			case Attack::Type::POTION:
				def_stat = characters[0].potion_recover;
				break;
			case Attack::Type::RELOAD:
				def_stat = characters[0].mana_recover;
				break;
			default:
				break;
			}
			int actual_stat = def_stat;
			if (actual_stat - 5 <= 0)
				actual_stat = 1;
			else
				actual_stat -= 5;

			std::vector<Vector2> stat_won;
			for (int j = 0; j < 10; j++) { //Do 10 * hundred battles and change the selected stat
				for (int i = 0; i < times_mov_test; i++) {
					int turn = 1;
					while (DoTurn(turn++, false)) {}
					if (characters[0].health > 0) {
						n_0_wins++;
						std::cout << "ch 0 won" << std::endl << std::endl;
					}
					else {
						std::cout << "ch 1 won" << std::endl << std::endl;
					}
					characters[0].Reset();
					switch (mov_test)
					{
					case Attack::Type::BASIC:
						characters[0].b_attack = actual_stat;
						break;
					case Attack::Type::SPECIAL:
						characters[0].sp_attack = actual_stat;
						break;
					case Attack::Type::POTION:
						characters[0].potion_recover = actual_stat;
						break;
					case Attack::Type::RELOAD:
						characters[0].mana_recover = actual_stat;
						break;
					default:
						break;
					}
					characters[1].Reset();
				}
				std::cout << "raising stat" << std::endl;
				stat_won.push_back(Vector2(actual_stat, n_0_wins));
				n_0_wins = 0;
				actual_stat++;
			}
			std::cout << "Simulation of stat " << characters[0].movements[mov_test]->ToString() << " finished" << std::endl;
			for (auto i = stat_won.begin(); i != stat_won.end(); i++) {
				std::cout << "value: " << (*i).first << " | won: " << (*i).second << "/100" << std::endl;
			}
			std::cout << std::endl;
		}
		else {
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
		}
		system("pause");
	}
	return false;
}

bool Battle::AreCharactersAlive()
{
	return characters[0].health > 0 && characters[1].health > 0;
}

bool Battle::DoTurn(int n_turn, bool print_stats)
{
		std::cout << "Turn number " << blue << n_turn << white << ", characters:" << std::endl << std::endl;
	if (print_stats) {
		characters[0].PrintStats();
		std::cout << std::endl << std::endl;
		characters[1].PrintStats();
		std::cout << std::endl << std::endl;
	}
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
	case Game::PlayMode::TEST_STAT:
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
			std::cout << yellow << "Player " << ch + 1 << " " << characters[ch].name << " got parried on last turn, cannot attack in this turn" << white << std::endl;
		}
		else if (characters[ch].parry) {
			std::cout << "Player " << ch + 1 << " " << characters[ch].name << " select a movement after have done parry:" << std::endl;
			std::cout << "(0) Basic" << std::endl;
			std::cout << "(1) Reload" << std::endl;
			std::cout << "(2) Potion" << std::endl;

			while (!(std::cin >> result) || result < 0 || result > 2 || (result == 2 && characters[ch].n_potions <= 0)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (result == 2 && characters[ch].n_potions <= 0)
					std::cout << red << "Cannot use Potion, character does not have any potion" << white << std::endl;
			}

			if (result == 1) //need to parse to normal attacks order
				result = 2;
			if (result == 2)
				result = 4;
		}
		else {
			std::cout << "Player " << ch + 1 << " " << characters[ch].name << " select a movement:" << std::endl;
			std::cout << characters[ch].MovementsToString() << std::endl;

			while (!(std::cin >> result) || result < 0 || result > characters[ch].movements.size() - 1 || (result == 1 && characters[ch].mana - characters[ch].mana_cost < 0) || (result == 4 && characters[ch].n_potions <= 0) || (result == 3 && characters[ch].n_parry <= 0)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (result == 1 && characters[ch].mana - characters[ch].mana_cost < 0)
					std::cout << red << "Cannot do Special, not enough mana" << white << std::endl;
				if (result == 3 && characters[ch].n_parry <= 0)
					std::cout << red << "Cannot use Parry, character does not have more parrys to do" << white << std::endl;
				if (result == 4 && characters[ch].n_potions <= 0)
					std::cout << red << "Cannot use Potion, character does not have any potion" << white << std::endl;
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
		std::cout << red << "Player " << characters[0].name << " got parried on last turn, cannot attack in this turn" << white << std::endl;
	}
	else if (characters[0].parry) {
		std::cout << "Player " << characters[0].name << " select a movement after have done parry:" << std::endl;
		std::cout << "(0) Basic" << std::endl;
		std::cout << "(1) Reload" << std::endl;
		std::cout << "(2) Potion" << std::endl;

		while (!(std::cin >> mov1) || mov1 < 0 || mov1 > 2 || (mov1 == 2 && characters[0].n_potions <= 0)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (mov1 == 2 && characters[0].n_potions <= 0)
				std::cout << red << "Cannot use Potion, character does not have any potion" << white << std::endl;
		}

		if (mov1 == 1) //need to parse to normal attacks order
			mov1 = 2;
		if (mov1 == 2)
			mov1 = 4;
	}
	else {
		std::cout << "Player " << characters[0].name << " select a movement:" << std::endl;
		std::cout << characters[0].MovementsToString() << std::endl;

		while (!(std::cin >> mov1) || mov1 < 0 || mov1 > characters[0].movements.size() - 1 || (mov1 == 1 && characters[0].mana - characters[0].mana_cost < 0) || (mov1 == 4 && characters[0].n_potions <= 0) || (mov1 == 3 && characters[0].n_parry <= 0)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (mov1 == 1 && characters[0].mana - characters[0].mana_cost < 0)
				std::cout << red << "Cannot do Special, not enough mana" << white << std::endl;
			if (mov1 == 3 && characters[0].n_parry <= 0)
				std::cout << red << "Cannot use Parry, character does not have more parrys to do" << white << std::endl;
			if (mov1 == 4 && characters[0].n_potions <= 0)
				std::cout << red << "Cannot use Potion, character does not have any potion" << white << std::endl;
		}
	}
	//AI
	if (characters[1].parried) {
		std::cout << red << characters[1].name << " got parried on last turn, cannot attack in this turn" << white << std::endl;
	}
	else if (characters[1].parry) {
		mov2 = (characters[1].n_potions <= 0) ? rand() % 2 : rand() % 3;

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
			std::cout << red << characters[i].name << " got parried on last turn, cannot attack in this turn" << white << std::endl;
		}
		else if (characters[i].parry) {
			mov2 = (characters[i].n_potions <= 0) ? rand() % 2 : rand() % 3;

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
	if (mov1 == Attack::POTION) {
		DoAttacks(0, 1, mov1, mov2);
	}
	else if (mov2 == Attack::POTION) {
		DoAttacks(1, 0, mov2, mov1);
	}
	else if (characters[0].speed > characters[1].speed) {
		DoAttacks(0, 1, mov1, mov2);
	}
	else if (characters[1].speed > characters[0].speed) {
		DoAttacks(1, 0, mov2, mov1);
	}
	else {
		if (std::rand() % 2 == 0) {
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
		std::cout << green << characters[first_attacker].name << " made a parry" << white << std::endl;
		characters[first_attacker].n_parry--;
		characters[first_attacker].parry = true;
		characters[second_attacker].parried = true;
	}
	else if (mov2 == Attack::Type::DODGE && (mov1 == Attack::Type::BASIC || mov1 == Attack::Type::SPECIAL)) {
		std::cout << green << characters[second_attacker].name << " made a parry" << white << std::endl;
		characters[second_attacker].n_parry--;
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
	//attacks.push_back(Attack::Type::BASIC); //Twice for more possibility to do a basic

	if (characters[charac].mana - characters[charac].mana_cost > 0) {
		attacks.push_back(Attack::Type::SPECIAL);
	}

	if (characters[charac].mana < characters[charac].mana_max * 0.5f) {
		attacks.push_back(Attack::Type::RELOAD);
	}

	if (characters[charac].n_parry > 0) {
		attacks.push_back(Attack::Type::DODGE);
	}

	if (characters[charac].n_potions > 0 && characters[charac].health < characters[charac].health_max * 0.5f) {
		attacks.push_back(Attack::Type::POTION);
		if(characters[charac].health < characters[charac].health_max * 0.25f)
			attacks.push_back(Attack::Type::POTION); // if is under 25% would be recommended to use a potion
	}

	return (int)attacks[rand() % attacks.size()];
}