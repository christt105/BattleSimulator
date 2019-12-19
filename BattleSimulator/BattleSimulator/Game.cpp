#include "Game.h"
#include <iostream>
#include <experimental/filesystem>

Game::Game()
{
}


Game::~Game()
{
}

void Game::MainMenu()
{
	system("cls");

	std::cout << "=========== Main Menu ===========" << std::endl << std::endl;

	for (int i = 0; i < (int)MenuEnum::MAX; i++)
		std::cout << "  (" << i << ") " << MainMenuToString((MenuEnum)i) << std::endl;

	int result = -1;
	while (!(std::cin >> result) || result <= (int)MenuEnum::NONE || result >= (int)MenuEnum::MAX) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	switch ((MenuEnum)result)
	{
	case Game::MenuEnum::QUIT:
		std::cout << "Exiting" << std::endl;
		std::cout << "Saving Info.." << std::endl;
		//TODO SAVE INFO OF PLAYS
		playing = false;
		break;
	case Game::MenuEnum::PLAY:
		PlayMenu();
		break;
	case Game::MenuEnum::CREDITS:
		std::cout << "System Made by:" << std::endl;
		std::cout << "\t* Christian Martinez De La Rosa: https://github.com/christt105" << std::endl;
		std::cout << "\t* Marc Galvez Llorens: https://github.com/optus23" << std::endl;
		std::cout << "\t* Lluis Moreu Farran: https://github.com/youis11" << std::endl << std::endl;
		std::system("pause");
		break;
	default:
		std::cout << "No behaviour defined to " << MainMenuToString((MenuEnum)result) << "(" << result << ")" << std::endl << std::endl;
		system("pause");
		break;
	}
}

void Game::PlayMenu()
{
	system("cls");

	std::cout << "=========== Play Mode ===========" << std::endl << std::endl;
	std::cout << "(0) 1 vs 1" << std::endl;
	std::cout << "(1) 1 vs AI" << std::endl;
	std::cout << "(2) AI vs AI" << std::endl;

	int result = -1;
	while (!(std::cin >> result) || result < 0 || result > 2) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	switch (result)
	{
	case 0:
		play_mode = PlayMode::HvsH;
		break;
	case 1:
		play_mode = PlayMode::HvsAI;
		break;
	case 2:
		play_mode = PlayMode::AIvsAI;
		break;
	default:
		std::cout << "No play mode for: " << result << std::endl << std::endl;
		system("pause");
		break;
	}

	SelectCharacterMenu();
}

void Game::SelectCharacterMenu()
{
	int character = 0;
	while (character < 2) {
		system("cls");

		std::cout << ((character == 0) ? "Select First Character" : "Select Second Character"); std::cout << std::endl << std::endl;

		std::vector<std::string> paths;
		int i = 0;
		for (auto entry : std::experimental::filesystem::directory_iterator("Characters")) {
			std::cout << "  (" << i << ") " << entry.path().filename().u8string() << std::endl;
			paths.push_back(entry.path().u8string());
			i++;
		}

		int result = -1;
		while (!(std::cin >> result) || result < 0 || result > paths.size()-1) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cout << "Loading character " << result << "(" << paths[result] << ")..." << std::endl;
		characters[character].Load(paths[result].c_str());
		paths.clear();

		character++;
	}
}

void Game::Update()
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
		
	}
	
}

std::string Game::MainMenuToString(MenuEnum type)
{
	switch (type)
	{
	case Game::MenuEnum::NONE:
		break;
	case Game::MenuEnum::QUIT:
		return std::string("Quit");
		break;
	case Game::MenuEnum::PLAY:
		return std::string("Play");
		break;
	case Game::MenuEnum::CREDITS:
		return std::string("Credits");
		break;
	case Game::MenuEnum::MAX:
		break;
	default:
		break;
	}

	return std::string();
}
