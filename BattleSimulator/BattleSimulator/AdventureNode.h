#pragma once
#include <string>
#include <vector>

struct Choice {
	Choice(const char* n, unsigned int to) :name(n), to_id(to) {}
	~Choice() {}
	std::string name;
	unsigned int to_id;
};

struct Combat {
	Combat() {}
	~Combat() {}
	std::string enemy;
	std::string song;
};

class AdventureNode
{
public:
	enum class Type {
		NONE = -1,
		TEXT, CHOICE, BATTLE, END,
		MAX
	};
public:
	AdventureNode();
	~AdventureNode();

	union {
		std::string text;
		Combat battle;
	};
	
	std::vector<Choice*> choices;

	Type type = Type::NONE;
	unsigned int id = 0;
	unsigned int to_id = 0;
};

