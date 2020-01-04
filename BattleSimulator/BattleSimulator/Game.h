#pragma once
#include "Character.h"

class Battle;

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
		HvsH, HvsAI, AIvsAI, TEST_ONE_MOV,
		MAX
	};

public:
	Game();
	~Game();

	void MainMenu();
	void PlayMenu();
	void AdventureMenu();
	void SelectCharacterMenu();
	void Update();

	inline bool IsPlaying() { return playing; }

private:
	std::string MainMenuToString(MenuEnum type);

public:
	Character characters[2];

private:
	bool playing = true;
	PlayMode play_mode = PlayMode::NONE;

	Battle* battle = nullptr;
};
