#pragma once

#include <string>

class Character;

class Attack
{
public:

	Attack(const char* name) : name(name) {}
	virtual ~Attack() {}

	std::string name;

	std::string ToString() const;
	virtual void DoAttack(Character* attacker, Character* objective) = 0;

};

class Tackle
	: public Attack 
{
public:
	Tackle() : Attack("Tackle") {}
	~Tackle() {}

	void DoAttack(Character* attacker, Character* objective) override;
};