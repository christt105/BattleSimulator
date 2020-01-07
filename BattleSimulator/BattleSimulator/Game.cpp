#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include "Game.h"
#include "Battle.h"
#include "json.hpp"
#include "Audio.h"

Game::Game()
{
	battle = new Battle();
	audio = new Audio();
}


Game::~Game()
{
	delete battle;
	delete audio;
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if ((*i).second->type == AdventureNode::Type::CHOICE)
			for (auto j = (*i).second->choices.begin(); j != (*i).second->choices.end(); j++)
				delete *j;
		delete (*i).second;
	}
}

void Game::MainMenu()
{
	system("cls");

	std::cout << "=========== Main Menu ===========" << std::endl << std::endl;
	audio->Play("Adventure/Audio/menu.mp3");
	for (int i = 0; i < (int)MenuEnum::MAX; i++)
		std::cout << "  (" << i << ") " << MainMenuToString((MenuEnum)i) << std::endl;

	int result = -1;
	while (!(std::cin >> result) || result <= (int)MenuEnum::NONE || result >= (int)MenuEnum::MAX) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	audio->Stop();

	switch ((MenuEnum)result)
	{
	case Game::MenuEnum::QUIT:
		std::cout << "Exiting" << std::endl;
		std::cout << "Saving Info.." << std::endl;
		//TODO SAVE INFO OF PLAYS
		playing = false;
		break;
	case Game::MenuEnum::SIMULATOR:
		PlayMenu();
		break;
	case Game::MenuEnum::GAME:
		AdventureMenu();
		break;
	case Game::MenuEnum::CREDITS:
		system("cls");
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
	std::cout << "(3) Test Movement" << std::endl;
	std::cout << "(4) Test Hundred battles" << std::endl;

	int result = -1;
	while (!(std::cin >> result) || result < 0 || result > 4) {
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
	case 3:
		play_mode = PlayMode::TEST_ONE_MOV;
		break;
	case 4:
		play_mode = PlayMode::TEST_HUNDRED_BATTLES;
		break;
	default:
		std::cout << "No play mode for: " << result << std::endl << std::endl;
		system("pause");
		break;
	}

	SelectCharacterMenu();
}

void Game::AdventureMenu()
{
	system("cls");

	std::cout << "=========== Adventure Mode ===========" << std::endl;
	AdventureNode* current = nodes[0u];
	
	while (current->type != AdventureNode::Type::END) {
		switch (current->type)
		{
		case AdventureNode::Type::TEXT: {
			std::ifstream f(current->text);
			std::string text((std::istreambuf_iterator<char>(f)),
				std::istreambuf_iterator<char>());
			auto c = text.begin();
			std::cout << std::endl;
			while (c != text.end()) {
				std::cout << *c;
				Sleep(10);
				c++;
			}
			std::cout << std::endl << std::endl;
			system("pause");
			current = nodes[current->to_id];
		}
			break;
		case AdventureNode::Type::BATTLE:
			std::cout << std::endl << "================== Battle Starts ==================" << std::endl << std::endl;
			audio->Play(current->battle.song.c_str());
			do
			{
			characters[0].Load(current->battle.player.c_str());
			characters[1].Load(current->battle.enemy.c_str());
			} while (battle->DoBattle(characters[0], characters[1], Game::PlayMode::ADVENTURE));

			audio->Stop();

			current = nodes[current->to_id];
			break;
		case AdventureNode::Type::CHOICE: {
			int n = 0;
			std::cout << std::endl;
			for (auto i = current->choices.begin(); i != current->choices.end(); i++) {
				std::cout << "(" << n << ") " << (*i)->name << std::endl;
				n++;
			}

			std::cout << std::endl;

			int result = -1;
			while (!(std::cin >> result) || result < 0 || result > current->choices.size()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			current = nodes[current->choices[result]->to_id];
		}
			break;
		default:
			break;
		}
	}
	std::cout << std::endl << "THE END" << std::endl << std::endl;
	system("pause");
}

void Game::LoadAdventure(const char * path)
{
	std::ifstream f(path);
	nlohmann::json json;
	f >> json;

	for (auto i = json["Adventure"].begin(); i != json["Adventure"].end(); i++) {
		std::string type = (*i)["type"];
		AdventureNode* node = new AdventureNode();
		node->id = (*i)["id"];
		if (type.compare("text") == 0) {
			node->text = (*i).value("text", "null");
			node->to_id = (*i)["to"];
			node->type = AdventureNode::Type::TEXT;
		}
		else if (type.compare("choice") == 0) {
			if ((*i).find("choices") != (*i).end()) {
				for (auto j = (*i)["choices"].begin(); j != (*i)["choices"].end(); j++) {
					std::string name = (*j).value("name", "null");
					unsigned int to = (*j)["to"];
					node->choices.push_back(new Choice(name.c_str(), to));
				}
			}
			node->type = AdventureNode::Type::CHOICE;
		}
		else if (type.compare("battle") == 0) {
			node->to_id = (*i)["to"];
			node->battle.player = (*i).value("player", "Characters/Player.txt");
			node->battle.enemy = (*i).value("enemy", "null");
			node->battle.song = (*i).value("song", "");
			node->type = AdventureNode::Type::BATTLE;
		}
		else if (type.compare("end") == 0) {
			node->type = AdventureNode::Type::END;
		}
		else {
			std::cout << "name in |type| node, " << type << " not correct" << std::endl;
			assert(true);
		}
		assert(nodes.find(node->id) == nodes.end());
		nodes[node->id] = node;
	}
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
			if (entry.path().extension().compare(".txt") == 0) {
				std::string name = entry.path().filename().u8string();
				name.erase(name.begin() + name.find(".txt"), name.end());
				std::cout << "  (" << i << ") " << name << std::endl;
				paths.push_back(entry.path().u8string());
				i++;
			}
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
	system("cls");

	while (battle->DoBattle(characters[0], characters[1], play_mode)) {}
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
	case Game::MenuEnum::SIMULATOR:
		return std::string("Simulator");
		break;
	case Game::MenuEnum::GAME:
		return std::string("Adventure");
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
