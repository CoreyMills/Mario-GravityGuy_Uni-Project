#include "SDL.h"
#include "GameScreen.h"


GameScreen::GameScreen(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS gameStatus)
{
	mGameStatus = gameStatus;

	mRenderer = renderer;

	mNextScreen = thisScreen;
	mScreenChanged = false;

	mMultiplayer = false;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	mBackgroundMusic->CleanChannel();
	delete mBackgroundMusic;
	mBackgroundMusic = NULL;
}

void GameScreen::Render()
{
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}

const SCREENS GameScreen::GetScreenToSwitchTo()
{
	return mNextScreen;
}

const bool GameScreen::CheckScreenChange()
{
	return mScreenChanged;
}

const bool GameScreen::CheckMultiplayer()
{
	return mMultiplayer;
}

void GameScreen::SetGameStatus(GAME_STATUS status)
{
	mGameStatus = status;
}

GAME_STATUS GameScreen::GetGameStatus()
{
	return mGameStatus;
}