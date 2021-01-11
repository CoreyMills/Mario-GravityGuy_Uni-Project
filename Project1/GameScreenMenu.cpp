#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS mCurrentGameStatus) : GameScreen(renderer, thisScreen, mCurrentGameStatus)
{
	SetUpLevel();
}

GameScreenMenu::~GameScreenMenu()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mBackgroundMusic;
	mBackgroundMusic = NULL;
}

void GameScreenMenu::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE, 0);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	if (!mGameChosen)
	{
		switch (e.type)
		{
			//KeyDown
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_1:
				mNextScreen = SCREEN_LEVEL1;
				mScreenChanged = true;
				break;
			case SDLK_2:
				//Load new the background Texture
				mBackgroundTexture->LoadFromFile("Images/HowManyPlayers.png");
				break;
			}
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_2:
				mGameChosen = true;
				break;
			}
		}
	}
	else
	{
		bool playerNotChosen = true;
		do
		{
			switch (e.type)
			{
				//KeyDown
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_1:
					playerNotChosen = false;
					mNextScreen = SCREEN_LEVEL2;
					mScreenChanged = true;
					break;
				case SDLK_2:
					mMultiplayer = true;
					playerNotChosen = false;
					mNextScreen = SCREEN_LEVEL2;
					mScreenChanged = true;
					break;
				default:
					playerNotChosen = true;
					break;
				}
			}
			break;
		} while (playerNotChosen == true);
	}
}

bool GameScreenMenu::SetUpLevel()
{
	mGameChosen = false;

	//Load the background Texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/StartMenu.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
}