#pragma once
#include <map>

class Audio
{
public:
	Audio();
	~Audio();

	void Play(const char* path);
	void PlayFX(const char* path);
	void Stop();

	std::map<std::string, std::string> songs;
	std::map<std::string, std::string> sfx;
	std::string actual_song;
};

