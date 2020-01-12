#pragma once
#include "Game.h"
#include "Character.h"

class Battle
{
public:
	Battle();
	~Battle();
	
	bool DoBattle(const Character& character1, const Character& character2, Game::PlayMode _mode);

private:
	bool AreCharactersAlive();
	bool DoTurn(int n_turn, bool print_stats = true);
	void DoHvHTurn();
	void DoAttacks(int first_attacker, int second_attacker, int mov1, int mov2);
	void DoHvAITurn();
	void CalculateFirstAttacker(int mov1, int mov2);
	int AIThinkMov(int i);
	void DoAIvAITurn();
	void TestMovementTurn();

	class Vector2 {
	public:
		Vector2(int a, int b) :first(a), second(b) {}
		int first = 0;
		int second = 0;
	};

	Character characters[2];
	Game::PlayMode mode = Game::PlayMode::NONE;

	int mov_test = -1;
	int times_mov_test = -1;
};

