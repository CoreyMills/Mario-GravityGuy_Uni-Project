#pragma once
#ifndef _SOUNDEFFECT_H
#define _SOUNDEFFECT_H

#include "Constants.h"
#include <SDL_mixer.h>
#include <iostream>

class SoundEffect
{
private:
	Mix_Chunk* mSoundEffect;

public:
	SoundEffect();
	~SoundEffect();

	bool LoadFromFile(char* path);
	void Play(int channel, int numLoops);
	void CleanChannel();
};
#endif