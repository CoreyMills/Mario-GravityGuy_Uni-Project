#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS mCurrentGameStatus, bool multiplayer) : GameScreen(renderer, thisScreen, mCurrentGameStatus)
{
	mMultiplayer = multiplayer;
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete mCamera;
	mCamera = NULL;

	mPlayerVArray.clear();
	mBarrierVArray.clear();
	mCheckpointVArray.clear();
	mStageVArray.clear();
	mStageEndVArray.clear();
	mLevelEndVArray.clear();

	delete mStageText;
	mStageText = NULL;
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	CheckCameraView();

	if (mStageText != NULL)
	{
		std::stringstream ss;
		ss << "Stage:" << mCurrentStage;
		char text[10];
		ss >> text;
		mStageText->SetText(text);

		mStageText->Update();
	}

	//All Players Lost
	if (mPlayerVArray.empty())
	{
		mGameStatus = ALL_PLAYERS_LOST;
		mNextScreen = SCREEN_GAMEOVER;
		mScreenChanged = true;
	}

	//remove stages, to save memory
	if (mStageVArray.size() >= 3)
	{
		mStageVArray.erase(mStageVArray.begin());
	}

	//check player collisions and updates
	for (int i = 0; i < mPlayerVArray.size(); i++)
	{
		CheckCollisions(mPlayerVArray.at(i));
		mPlayerVArray.at(i)->Update(deltaTime, e);
	}

	//move all objects to make camera illusion = (next 4 for loops)
	for (int i = 0; i < mBarrierVArray.size(); i++)
	{
		mBarrierVArray.at(i)->SetPosition(mBarrierVArray.at(i)->GetPosition().x - mCamera->x,
			mBarrierVArray.at(i)->GetPosition().y);
	}

	for (int i = 0; i < mCheckpointVArray.size(); i++)
	{
		mCheckpointVArray.at(i)->SetPosition(mCheckpointVArray.at(i)->GetPosition().x - mCamera->x,
			mCheckpointVArray.at(i)->GetPosition().y);
	}

	for (int i = 0; i < mStageEndVArray.size(); i++)
	{
		mStageEndVArray.at(i)->SetPosition(mStageEndVArray.at(i)->GetPosition().x - mCamera->x,
			mStageEndVArray.at(i)->GetPosition().y);
	}

	for (int i = 0; i < mLevelEndVArray.size(); i++)
	{
		mLevelEndVArray.at(i)->SetPosition(mLevelEndVArray.at(i)->GetPosition().x - mCamera->x,
			mLevelEndVArray.at(i)->GetPosition().y);
	}

	if (mCamera->x < 0.23f)
	{
		mCamera->x += 0.00001f;
	}

	mCameraTravelledBy += mCamera->x;
}

void GameScreenLevel2::Render()
{
	//Draw Background
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE, 0);

	for (int i = 0; i < mBarrierVArray.size(); i++)
	{
		mBarrierVArray.at(i)->Render();
	}

	if (mStageText != NULL)
	{
		mStageText->Render();
	}

	for (int i = 0; i < mPlayerVArray.size(); i++)
	{
		mPlayerVArray.at(i)->Render();
	}
}

void GameScreenLevel2::SpawnEmptyGameObject(float x, float y, int vArrayChosen)
{
	GameObject * gameObject;

	switch (vArrayChosen)
	{
	case 0:
		gameObject = new GameObject(mRenderer, "Images/Blank.png");
		gameObject->SetPosition((((x + mLevelWidth) * gameObject->GetCollisionBox().width) - mCameraTravelledBy),
			(y * gameObject->GetCollisionBox().height));

		mCheckpointVArray.push_back(gameObject);
		break;
	case 1:
		gameObject = new GameObject(mRenderer, "Images/Blank.png");
		gameObject->SetPosition((((x + mLevelWidth) * gameObject->GetCollisionBox().width) - mCameraTravelledBy),
			(y * gameObject->GetCollisionBox().height));

		mStageEndVArray.push_back(gameObject);
		break;
	case 2:
		gameObject = new GameObject(mRenderer, "Images/Blank.png");
		gameObject->SetPosition((((x + mLevelWidth) * gameObject->GetCollisionBox().width) - mCameraTravelledBy),
			(y * gameObject->GetCollisionBox().height));

		mLevelEndVArray.push_back(gameObject);
		break;
	case 3:
		gameObject = new GameObject(mRenderer, "Images/Barrier.png");
		gameObject->SetPosition((((x + mLevelWidth) * gameObject->GetCollisionBox().width) - mCameraTravelledBy),
			(y * gameObject->GetCollisionBox().height));

		mBarrierVArray.push_back(gameObject);
		break;
	default:
		gameObject = new GameObject(mRenderer, "Images/Blank.png");
		break;
	}
}

void GameScreenLevel2::SpawnStage()
{
	LevelMap* stageMap = new LevelMap();

	std::stringstream ss;
	std::string tempString = new char();
	int randStage = rand() % 6 + 1;

	if (mStageVArray.empty())
	{
		ss << "Levels/Level2/StageStart.txt";
	}
	else
	{
		if (mCurrentStage >= mStagesToComplete)
		{
			ss << "Levels/Level2/StageEnd.txt";
		}
		else
		{
			ss << "Levels/Level2/Stage" << randStage << ".txt";
		}
	}

	tempString = ss.str();
	stageMap->LoadFromFile(tempString);

	for (unsigned int i = 0; i < stageMap->GetMapHeight(); i++)
	{
		for (unsigned int j = 0; j < stageMap->GetMapWidth(); j++)
		{
			int tileValue = stageMap->GetTileValue(j, i);

			switch (tileValue)
			{
			case 1:
				SpawnEmptyGameObject(j, i, 3);
				break;
			case 3:
				SpawnEmptyGameObject(j, i, 0);
				break;
			case 4:
				SpawnEmptyGameObject(j, i, 1);
				break;
			case 5:
				SpawnEmptyGameObject(j, i, 2);
				break;
			}
		}
	}

	mLevelWidth += stageMap->GetMapWidth();

	mStageVArray.push_back(stageMap);
}

void GameScreenLevel2::CheckCollisions(GravityGuy* player)
{
	//check if any players collide with the barriers
	for (int i = 0; i < mBarrierVArray.size(); i++)
	{
		bool barrierHit = false;
		player->SetBlocked(false, 0);

		barrierHit = Collisions::Instance()->Box(player->GetCollisionBox(), mBarrierVArray.at(i)->GetCollisionBox());
		if (barrierHit)
		{
			Rect2D* tempRect = new Rect2D(mBarrierVArray.at(i)->GetCollisionBox());
			int blockDir = Collisions::Instance()->Collision(player, tempRect);
			player->SetBlocked(true, blockDir);
			player->SetTouchedBarrier(true, blockDir);

			continue;
		}
	}

	//check if any players collide with the checkpoints
	bool checkpointHit = false;
	for (int i = 0; i < mCheckpointVArray.size(); i++)
	{
		checkpointHit = Collisions::Instance()->Box(player->GetCollisionBox(), mCheckpointVArray.at(i)->GetCollisionBox());
		
		if (checkpointHit)
		{
			mCheckpointVArray.clear();
			SpawnStage();
			break;
		}
	}

	//check if any players collide with end of the stage
	bool StageEndHit = false;
	for (int i = 0; i < mStageEndVArray.size(); i++)
	{
		StageEndHit = Collisions::Instance()->Box(player->GetCollisionBox(), mStageEndVArray.at(i)->GetCollisionBox());
		
		if (StageEndHit)
		{
			mStageEndVArray.clear();
			mCurrentStage++;
			player->SetToCenter(true);
			break;
		}
	}

	//check if any players collide with end of level
	bool LevelEndHit = false;
	for (int i = 0; i < mLevelEndVArray.size(); i++)
	{
		LevelEndHit = Collisions::Instance()->Box(player->GetCollisionBox(), mLevelEndVArray.at(i)->GetCollisionBox());

		//Player WON
		if (LevelEndHit)
		{
			mLevelEndVArray.clear();

			if (!mMultiplayer)
			{
				mGameStatus = ALL_PLAYERS_WON;
				mNextScreen = SCREEN_GAMEOVER;
				mScreenChanged = true;
			}
			else
			{
				switch (player->GetPlayerNum())
				{
				case 1:
					mGameStatus = PLAYER1_WON;
					mNextScreen = SCREEN_GAMEOVER;
					mScreenChanged = true;
					break;
				case 2:
					mGameStatus = PLAYER2_WON;
					mNextScreen = SCREEN_GAMEOVER;
					mScreenChanged = true;
					break;
				}
				break;
			}
		}
	}
}

void GameScreenLevel2::CheckCameraView()
{
	for (int i = 0; i < mPlayerVArray.size(); i++)
	{
		if (CheckOutOfBounds(mPlayerVArray.at(i), mCamera))
		{
			mPlayerVArray.erase(mPlayerVArray.begin() + i);
		}
	}

	for (int i = 0; i < mBarrierVArray.size(); i++)
	{
		if (CheckOutOfBounds(mBarrierVArray.at(i), mCamera))
		{
			mBarrierVArray.erase(mBarrierVArray.begin() + i);
		}
	}

	for (int i = 0; i < mStageEndVArray.size(); i++)
	{
		if (CheckOutOfBounds(mStageEndVArray.at(i), mCamera))
		{
			mStageEndVArray.erase(mStageEndVArray.begin() + i);
		}
	}
}

bool GameScreenLevel2::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundGG.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	mStagesToComplete = 1;
	mCurrentStage = 1;
	mLevelWidth = 0;
	mLevelHeight = 0;

	SpawnStage();

	mCamera = new Rect2D(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	mCameraTravelledBy = 0;

	GravityGuy* player = new GravityGuy(mRenderer, "Images/GravityGuy1.png", FACING_RIGHT, 1);
	player->SetPosition(100, 224);
	player->SetToCenter(true);
	mPlayerVArray.push_back(player);

	if (mMultiplayer)
	{
		GravityGuy* player = new GravityGuy(mRenderer, "Images/GravityGuy2.png", FACING_RIGHT, 2);
		player->SetPosition(100, 224);
		player->SetGravity(NORTH);
		player->SetToCenter(true);
		mPlayerVArray.push_back(player);
	}

	mStageText = new Text2D(mRenderer, "Stage:0", "Fonts/ARIAL.TTF", 200, 50);

	mBackgroundMusic = new SoundEffect();
	mBackgroundMusic->LoadFromFile("Music/GravityGuy_Background.wav");
	mBackgroundMusic->Play(0, -1);
}

bool GameScreenLevel2::CheckOutOfBounds(GameObject* object, Rect2D* boundaryBox)
{
	if (object->GetPosition().y + object->GetCollisionBox().height < boundaryBox->y
		|| object->GetPosition().x + object->GetCollisionBox().width < boundaryBox->x
		|| object->GetPosition().y > boundaryBox->y + boundaryBox->height)
	{
		return true;
	}

	return false;
}