#include <iostream>
#include <random>
#include <time.h>
#include "Character.h"
#include "Game.h"

Game* game = nullptr;

int main() {
	std::srand((int)time(NULL));

	game = new Game();
	game->LoadAdventure("Adventure/adventure.json");
	
	while (game->IsPlaying()) {
		game->MainMenu();
	}

	getchar();
	system("pause");

	delete game;

	return 0;
}