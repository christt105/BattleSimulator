#pragma once
#include <string>
#include <vector>

struct Choice {
	std::string name;
	unsigned int to_id;
};

struct Combat {
	std::string enemy;
	std::string song;
};

union Node {
	std::string text;
	std::vector<Choice> choices;
	Combat battle;
};

class AdventureNode
{
	enum Type {
		NONE = -1,
		TEXT, CHOICE, BATTLE,
		MAX
	};
public:
	AdventureNode();
	~AdventureNode();

	//Node node;

	Type type = NONE;
	unsigned int id = 0;
	unsigned int to_id = 0;
};

