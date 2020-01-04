#include "Audio.h"
#include <Windows.h>


Audio::Audio()
{
}


Audio::~Audio()
{
}

void Audio::Play(const char * path)
{
	//PlaySound(TEXT(path), NULL, SND_FILENAME);
	mciSendString("open Adventure/Audio/dialga.mp3 type mpegvideo alias song1", NULL, 0, 0);
	mciSendString("play song1", NULL, 0, 0);
	//mciSendString("close song1", NULL, 0, 0);
}
