#pragma once
#ifndef _GAMESCREENGAMEOVER_H
#define _GAMESCREENGAMEOVER_H

#include "SDL.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "SoundEffect.h"

#include <vector>
#include <iostream>

class Texture2D;

class GameScreenGameOver : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	SoundEffect* mBackgroundMusic;

	SoundEffect* mApplauseSE;
	SoundEffect* mBooingSE;

	bool SetUpLevel();

public:
	GameScreenGameOver(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS mCurrentGameStatus);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
#endif