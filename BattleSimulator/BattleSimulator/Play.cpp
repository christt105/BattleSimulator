#include "Play.h"
#include <iostream>
#include <Windows.h>

Play::Play()
{
}


Play::~Play()
{
}

void Play::Update()
{
	bool repeat = true;
	bool write = true;
	int select = 0;
	bool down = false;
	bool up = false;
	while (repeat) {
		if (write) {
			std::cout << "Character 1 turn:" << std::endl;
			for (int i = 0; i < 3; i++) {
				if (select == i) std::cout << ">  ";
				else std::cout << "  ";
				std::cout << "Choice " << i + 1 << std::endl;
			}
			write = false;
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			if (!down) {
				down = true;
				system("cls");
				write = true;
				if (select < 2)
					select++;
			}
		}
		else {
			down = false;
		}
		if (GetAsyncKeyState(VK_UP)) {
			if (!up) {
				up = true;
				system("cls");
				write = true;
				if (select > 0)
					select--;
			}
		}
		else {
			up = false;
		}
	}
	
}
