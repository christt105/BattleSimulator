#include <iostream>
#include "Character.h"
#include "Play.h"

int main() {
	Play* play = new Play();

	play->characters[0] = Character(15, 10, 5, 100);
	play->characters[1] = Character(10, 15, 3, 120);

	std::cout << "Character 1: " + play->characters[0].ToString() << std::endl;
	std::cout << "Character 2: " + play->characters[1].ToString() << std::endl;

	while (true) {
		play->Update();
	}

	getchar();
	system("pause");

	return 0;
}