#include "Audio.h"
#include <Windows.h>
#include <string>


Audio::Audio()
{
}


Audio::~Audio()
{
}

void Audio::Play(const char * path)
{
	if (songs.find(path) == songs.end()) {
		songs[path] = "song" + std::to_string(songs.size());
		mciSendString((std::string("open ") + path + " type mpegvideo alias " + songs[path]).c_str(), NULL, 0, 0);
	}

	mciSendString(("play " + songs[path] + " from 0 repeat").c_str(), NULL, 0, 0);
	actual_song.assign(songs[path]);
}
void Audio::Close()
{
	mciSendString(("stop " + actual_song).c_str(), NULL, 0, 0);
}
