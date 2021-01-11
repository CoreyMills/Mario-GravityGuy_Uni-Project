#pragma once

#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenGameOver.h"

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;

	GAME_STATUS mCurrentGameStatus;

	bool mMultiplayer;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
};
#endif