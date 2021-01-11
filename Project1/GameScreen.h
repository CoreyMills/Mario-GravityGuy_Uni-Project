#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include "SoundEffect.h"

class Texture2D;

class GameScreen
{
protected:
	SDL_Renderer* mRenderer;

	Texture2D* mBackgroundTexture;
	SoundEffect* mBackgroundMusic;

	GAME_STATUS mGameStatus;

	SCREENS mNextScreen;
	bool mScreenChanged;

	bool mMultiplayer;

public:
	GameScreen(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS gameStatus);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	const SCREENS GetScreenToSwitchTo();
	const bool CheckScreenChange();
	const bool CheckMultiplayer();

	void SetGameStatus(GAME_STATUS status);

	GAME_STATUS GetGameStatus();
};
#endif