#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
}

SoundEffect::~SoundEffect()
{
	mSoundEffect = NULL;
}

bool SoundEffect::LoadFromFile(char* path)
{
	mSoundEffect = Mix_LoadWAV(path);

	if (mSoundEffect == NULL)
	{
		std::cout << "Failed to load sound effect! Error: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

void SoundEffect::Play(int channel, int numLoops)
{
	if (Mix_PlayChannel(channel, mSoundEffect, numLoops) == -1)
	{
		std::cout << "Mix_PlayChannel: = " << Mix_GetError() << std::endl;
	}
}

void SoundEffect::CleanChannel()
{
	Mix_HaltChannel(-1);
}