#include <iostream>
#include <random>
#include <time.h>
#include "Character.h"
#include "Game.h"

int main() {
	Game game;

	std::srand((int)time(NULL));
	
	while (game.IsPlaying()) {
		game.MainMenu();
	}

	getchar();
	system("pause");

	return 0;
}