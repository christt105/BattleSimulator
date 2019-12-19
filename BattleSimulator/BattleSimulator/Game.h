#pragma once
#include "Character.h"
#include "Turn.h"

class Game
{
	enum class MenuEnum {
		NONE = -1,
		
		QUIT, 
		PLAY, 
		CREDITS,

		MAX
	};

	enum class PlayMode {
		NONE = -1,
		HvsH, HvsAI, AIvsAI,
		MAX
	};

public:
	Game();
	~Game();

	void MainMenu();
	void PlayMenu();
	void SelectCharacterMenu();
	void Update();

	inline bool IsPlaying() { return playing; }

private:
	std::string MainMenuToString(MenuEnum type);

public:
	Character characters[2];
	Turn turn;

private:
	bool playing = true;
	PlayMode play_mode = PlayMode::NONE;
};

