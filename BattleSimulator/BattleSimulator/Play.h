#pragma once
#include "Character.h"
#include "Turn.h"

class Play
{
public:
	Play();
	~Play();

	void Update();

public:
	Character characters[2];
	Turn turn;
};

