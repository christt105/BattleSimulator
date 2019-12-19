#include <iostream>
#include "Character.h"
#include "Game.h"

int main() {
	Game game;
	
	while (game.IsPlaying()) {
		game.MainMenu();
	}

	getchar();
	system("pause");

	return 0;
}