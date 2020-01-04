#include <iostream>
#include <random>
#include <time.h>
#include "Character.h"
#include "Game.h"

int main() {
	std::srand((int)time(NULL));

	Game game;
	game.LoadAdventure("Adventure/adventure.json");
	
	while (game.IsPlaying()) {
		game.MainMenu();
	}

	getchar();
	system("pause");

	return 0;
}