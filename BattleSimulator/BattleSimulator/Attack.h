#pragma once

#include <string>

class Character;

class Attack
{
public:
	enum Type {
		NONE = -1,
		BASIC, SPECIAL, RELOAD, DODGE, POTION,
		MAX
	};

	Attack(const char* name, Type type) : name(name), type(type) {}
	virtual ~Attack() {}

	std::string name;
	Type type = NONE;
	std::string ToString() const;
	virtual bool DoAttack(Character* attacker, Character* objective) = 0; //return false if miss
};

class Basic
	: public Attack
{
public:
	Basic() : Attack("Basic", BASIC) {}
	~Basic() {}

	bool DoAttack(Character* attacker, Character* objective) override;
};

class Special
	: public Attack
{
public:
	Special() : Attack("Special", SPECIAL) {}
	~Special() {}

	bool DoAttack(Character* attacker, Character* objective) override;
};

class Reload
	: public Attack
{
public:
	Reload() : Attack("Reload", RELOAD) {}
	~Reload() {}

	bool DoAttack(Character* attacker, Character* objective) override;
};

class Dodge
	: public Attack
{
public:
	Dodge() : Attack("Parry", DODGE) {}
	~Dodge() {}

	bool DoAttack(Character* attacker, Character* objective) override;
};

class Potion
	: public Attack
{
public:
	Potion() : Attack("Potion", POTION) {}
	~Potion() {}

	bool DoAttack(Character* attacker, Character* objective) override;
};
