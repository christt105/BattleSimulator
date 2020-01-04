#pragma once

class Audio
{
public:
	Audio();
	~Audio();

	void Play(const char* path);
	void Close(const char* path);
};

