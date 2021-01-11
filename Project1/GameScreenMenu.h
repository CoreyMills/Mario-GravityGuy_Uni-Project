#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "SDL.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "SoundEffect.h"

#include <vector>
#include <iostream>

class Texture2D;

class GameScreenMenu : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	SoundEffect* mBackgroundMusic;

	bool mGameChosen;

	bool SetUpLevel();

public:
	GameScreenMenu(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS mCurrentGameStatus);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
#endif