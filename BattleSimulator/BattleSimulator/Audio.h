#pragma once
#include <map>

class Audio
{
public:
	Audio();
	~Audio();

	void Play(const char* path);
	void Close();

	std::map<std::string, std::string> songs;
	std::string actual_song;
};

