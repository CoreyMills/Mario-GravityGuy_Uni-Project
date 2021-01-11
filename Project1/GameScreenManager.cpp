#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;

	mCurrentGameStatus = RUNNING;

	mMultiplayer = false;

	//setup first screen
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

	mCurrentGameStatus = mCurrentScreen->GetGameStatus();
	mMultiplayer = mCurrentScreen->CheckMultiplayer();

	if (mCurrentScreen->CheckScreenChange())
	{
		ChangeScreen(mCurrentScreen->GetScreenToSwitchTo());
	}
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
		mCurrentScreen = NULL;
	}

	switch (newScreen)
	{
	case SCREEN_INTRO:
		GameScreenLevel1* Screen_Intro;
		Screen_Intro = new GameScreenLevel1(mRenderer, SCREEN_INTRO, mCurrentGameStatus);
		mCurrentScreen = (GameScreen*)Screen_Intro;
		Screen_Intro = NULL;
		break;
	case SCREEN_MENU:
		GameScreenMenu * Screen_Menu;
		Screen_Menu = new GameScreenMenu(mRenderer, SCREEN_MENU, mCurrentGameStatus);
		mCurrentScreen = (GameScreen*)Screen_Menu;
		Screen_Menu = NULL;
		break;
	case SCREEN_LEVEL1:
		GameScreenLevel1* Screen_Level1;
		Screen_Level1 = new GameScreenLevel1(mRenderer, SCREEN_LEVEL1, mCurrentGameStatus);
		mCurrentScreen = (GameScreen*)Screen_Level1;
		Screen_Level1 = NULL;
		break;
	case SCREEN_LEVEL2:
		GameScreenLevel2* Screen_Level2;
		Screen_Level2 = new GameScreenLevel2(mRenderer, SCREEN_LEVEL2, mCurrentGameStatus, mMultiplayer);
		mCurrentScreen = (GameScreen*)Screen_Level2;
		Screen_Level2 = NULL;
		break;
	case SCREEN_GAMEOVER:
		GameScreenGameOver* Screen_GameOver;
		Screen_GameOver = new GameScreenGameOver(mRenderer, SCREEN_GAMEOVER, mCurrentGameStatus);
		mCurrentScreen = (GameScreen*)Screen_GameOver;
		Screen_GameOver = NULL;
		break;
	case SCREEN_HIGHSCORES:
		GameScreenLevel1* Screen_HighScores;
		Screen_HighScores = new GameScreenLevel1(mRenderer, SCREEN_HIGHSCORES, mCurrentGameStatus);
		mCurrentScreen = (GameScreen*)Screen_HighScores;
		Screen_HighScores = NULL;
		break;
	default:
		break;
	}
}