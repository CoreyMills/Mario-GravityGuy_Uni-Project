#include "GameScreenGameOver.h"

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS gameStatus) : GameScreen(renderer, thisScreen, gameStatus)
{
	SetUpLevel();
}

GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mBackgroundMusic;
	mBackgroundMusic = NULL;

	delete mApplauseSE;
	mApplauseSE = NULL;

	delete mBooingSE;
	mBooingSE = NULL;
}

void GameScreenGameOver::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE, 0);
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		//KeyDown
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_h:
			if (mGameStatus == ALL_PLAYERS_WON || mGameStatus == ALL_PLAYERS_LOST || 
				mGameStatus == PLAYER1_WON || mGameStatus == PLAYER2_WON)
			{
				mNextScreen = SCREEN_HIGHSCORES;
				mScreenChanged = true;
			}
			break;
		case SDLK_m:
			if (mGameStatus == ALL_PLAYERS_WON || mGameStatus == ALL_PLAYERS_LOST || 
				mGameStatus == PLAYER1_WON || mGameStatus == PLAYER2_WON)
			{
				mNextScreen = SCREEN_MENU;
				mScreenChanged = true;
			}
			break;
		}
	}
}

bool GameScreenGameOver::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);

	mApplauseSE = new SoundEffect();
	mApplauseSE->LoadFromFile("Music/Applause.wav");

	mBooingSE = new SoundEffect();
	mBooingSE->LoadFromFile("Music/Boo.wav");

	if (mGameStatus == ALL_PLAYERS_WON)
	{
		mApplauseSE->Play(1, 0);
		if (!mBackgroundTexture->LoadFromFile("Images/WinScreen.png"))
		{
			std::cout << "Failed to load background texture!" << std::endl;
			return false;
		}
	}
	else if(mGameStatus == ALL_PLAYERS_LOST)
	{
		mBooingSE->Play(1, 0);
		if (!mBackgroundTexture->LoadFromFile("Images/DeathScreen.png"))
		{
			std::cout << "Failed to load background texture!" << std::endl;
			return false;
		}
	}
	else if (mGameStatus == PLAYER1_WON)
	{
		mApplauseSE->Play(1, 0);

		if (!mBackgroundTexture->LoadFromFile("Images/P1WinScreen.png"))
		{
			std::cout << "Failed to load background texture!" << std::endl;
			return false;
		}
	}
	else if (mGameStatus == PLAYER2_WON)
	{
		mApplauseSE->Play(1, 0);
		if (!mBackgroundTexture->LoadFromFile("Images/P2WinScreen.png"))
		{
			std::cout << "Failed to load background texture!" << std::endl;
			return false;
		}
	}
}