#pragma once
#include <map>
#include "Character.h"
#include "AdventureNode.h"

class Battle;
class Audio;

class Game
{
	enum class MenuEnum {
		NONE = -1,
		
		QUIT, 
		GAME,
		SIMULATOR, 
		CREDITS,

		MAX
	};

public:
	enum class PlayMode {
		NONE = -1,
		HvsH, HvsAI, AIvsAI, TEST_ONE_MOV, TEST_HUNDRED_BATTLES, ADVENTURE,
		MAX
	};

public:
	Game();
	~Game();

	void MainMenu();
	void PlayMenu();
	void AdventureMenu();
	void LoadAdventure(const char* path);
	void SelectCharacterMenu();

	inline bool IsPlaying() { return playing; }

private:
	std::string MainMenuToString(MenuEnum type);

public:
	Character characters[2];
	Audio* audio = nullptr;

private:
	bool playing = true;
	PlayMode play_mode = PlayMode::NONE;

	Battle* battle = nullptr;

	std::map<unsigned int, AdventureNode*> nodes;
};

extern Game* game;