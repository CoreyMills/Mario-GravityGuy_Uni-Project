#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS mCurrentGameStatus) : GameScreen(renderer, thisScreen, mCurrentGameStatus)
{
	mLevelMap = NULL;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	mKoopaV.clear();
	mGoombaV.clear();
	mCoinsV.clear();

	delete mLevelMap;
	mLevelMap = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	delete mMarioCharacter;
	mMarioCharacter = NULL;

	mPowBlockSE->CleanChannel();
	delete mPowBlockSE;
	mPowBlockSE = NULL;

	mCoinCollectedSE->CleanChannel();
	delete mCoinCollectedSE;
	mCoinCollectedSE = NULL;

	delete mScoreText;
	mScoreText = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//check spawning
	PeriodicSpawning(deltaTime);

	//apply screen shake
	if (mScreenShake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//end screen shake
		if (mScreenShakeTime <= 0.0f)
		{
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	//Update player
	if (mMarioCharacter != NULL)
	{
		if (mScoreText != NULL)
		{
			std::stringstream ss;
			ss << "Score:" << mMarioCharacter->GetPointsAmount();
			char text[10];
			ss >> text;
			mScoreText->SetText(text);

			mScoreText->Update();
		}

		//Player Won
		if (mMarioCharacter->GetPointsAmount() >= 100)
		{
			mGameStatus = ALL_PLAYERS_WON;
			mNextScreen = SCREEN_GAMEOVER;
			mScreenChanged = true;
		}

		mMarioCharacter->Update(deltaTime, e);

		UpdatePowBlock();
		UpdateEnemies(deltaTime, e);
		UpdateCoins(deltaTime, e);

		//Delete Dead Characters
		DeleteDeadCharacters();
	}
	//Player Lost
	else
	{
		mGameStatus = ALL_PLAYERS_LOST;
		mNextScreen = SCREEN_GAMEOVER;
		mScreenChanged = true;
	}
}

void GameScreenLevel1::Render()
{
	if (mScoreText != NULL)
	{
		mScoreText->Render();
	}

	//draw Koopas
	for (int i = 0; i < mKoopaV.size(); i++)
	{
		mKoopaV.at(i)->Render();
	}

	//draw Goombas
	for (int i = 0; i < mGoombaV.size(); i++)
	{
		mGoombaV.at(i)->Render();
	}

	//draw Coins
	for (int i = 0; i < mCoinsV.size(); i++)
	{
		mCoinsV.at(i)->Render();
	}

	//draw Player
	if (mMarioCharacter != NULL)
	{
		mMarioCharacter->Render();
	}

	//render powBlock
	if (mPowBlock != NULL)
	{
		mPowBlock->Render();
	}

	//Draw Background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos + 64), SDL_FLIP_NONE, 0);
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!mCoinsV.empty())
	{
		for (unsigned int i = 0; i < mCoinsV.size(); i++)
		{
			mCoinsV.at(i)->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(mCoinsV.at(i)->GetCollisionCircle(), mMarioCharacter->GetCollisionCircle()))
			{
				mCoinsV.at(i)->SetState(FOUND);
				CollectCoins(1, i);
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mKoopaV.empty())
	{
		for (unsigned int i = 0; i < mKoopaV.size(); i++)
		{
			if (mKoopaV.at(i)->GetPosition().y > 300.0f)
			{
				if ((mKoopaV.at(i)->GetPosition().x < (float)(-mKoopaV.at(i)->GetCollisionBox().width*0.5f)) ||
					(mKoopaV.at(i)->GetPosition().x > SCREEN_WIDTH - (float)(mKoopaV.at(i)->GetCollisionBox().width*0.55f)))
				{
					mKoopaV.at(i)->SetState(DEAD);
				}
			}

			mKoopaV.at(i)->Update(deltaTime, e);

			if (!mMarioCharacter->CheckProtected())
			{
				if (Collisions::Instance()->Circle(mKoopaV.at(i)->GetCollisionCircle(), mMarioCharacter->GetCollisionCircle()))
				{

					if (mKoopaV.at(i)->CheckInjured())
					{
						mKoopaV.at(i)->SetState(DEAD);
						mMarioCharacter->SetPointsAmount(mMarioCharacter->GetPointsAmount() + 15);
					}
					else
					{

						if (mMarioCharacter->CheckDamaged())
						{
							mMarioCharacter->SetState(DEAD);
						}
						else
						{
							mMarioCharacter->SetDamaged(true);
							mMarioCharacter->SetProtected(true);
						}
					}
				}
			}
		}
	}

	if (!mGoombaV.empty())
	{
		for (unsigned int i = 0; i < mGoombaV.size(); i++)
		{
			//walked off screen
			if (mGoombaV.at(i)->GetPosition().y > SCREEN_HEIGHT)
			{
				mGoombaV.at(i)->SetState(DEAD);
			}

			//update
			mGoombaV.at(i)->Update(deltaTime, e);

			if (!mMarioCharacter->CheckProtected())
			{
				if (Collisions::Instance()->Box(mGoombaV.at(i)->GetKillingRect(), mMarioCharacter->GetCollisionBox()))
				{
					if (mGoombaV.at(i)->GetState() != INJURED)
					{
						mMarioCharacter->SetPointsAmount(mMarioCharacter->GetPointsAmount() + 20);
					}

					mGoombaV.at(i)->TakeDamage();
					continue;
				}

				if (mGoombaV.at(i)->GetState() != INJURED)
				{
					if (Collisions::Instance()->Circle(mGoombaV.at(i)->GetCollisionCircle(), mMarioCharacter->GetCollisionCircle()))
					{
						if (mMarioCharacter->CheckDamaged())
						{
							mMarioCharacter->SetState(DEAD);
						}
						else
						{
							mMarioCharacter->SetDamaged(true);
							mMarioCharacter->SetProtected(true);
						}
					}
				}
			}
		}
	}
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (mPowBlock != NULL)
	{
		Rect2D tempMarioRect = { mMarioCharacter->GetCollisionBox() };
		Rect2D tempPowRect = { mPowBlock->GetCollisionBox() };

		if (!mPowBlock->IsAvailable())
		{
			delete mPowBlock;
			mPowBlock = NULL;
		}
		else
		{
			if (Collisions::Instance()->Box(tempMarioRect, tempPowRect))
			{
				if (mMarioCharacter->GetJumping() &&
					tempMarioRect.y > tempPowRect.y + (tempPowRect.height* 0.95))
				{
					DoScreenShake();
					mPowBlock->TakeAHit();
					mMarioCharacter->CancelJump();
					mPowBlockSE->Play(1, 0);
				}
				else
				{
					Collisions::Instance()->Collision(mMarioCharacter, &tempPowRect);
				}
			}
		}
	}
}

void GameScreenLevel1::CollectCoins(int coinsAmount, int coinIndex)
{
	mCoinsV.erase(mCoinsV.begin() + coinIndex);
	mMarioCharacter->SetCoinsAmount(mMarioCharacter->GetCoinsAmount() + coinsAmount);
	mMarioCharacter->SetPointsAmount(mMarioCharacter->GetPointsAmount() + 30);
	mCoinCollectedSE->Play(1, 0);
}

void GameScreenLevel1::DeleteDeadCharacters()
{
	if (mMarioCharacter->GetState() == DEAD)
	{
		delete mMarioCharacter;
		mMarioCharacter = NULL;
	}

	for (int i = 0; i < mKoopaV.size(); i++)
	{
		if (mKoopaV.at(i)->GetState() == DEAD)
		{
			mKoopaV.erase(mKoopaV.begin() + i);
		}
	}

	for (int i = 0; i < mGoombaV.size(); i++)
	{
		if (mGoombaV.at(i)->GetState() == DEAD)
		{
			mGoombaV.erase(mGoombaV.begin() + i);
		}
	}
}

void GameScreenLevel1::CreateCoin(FACING direction, float x, float y)
{
	ItemCoin* coinItem = new ItemCoin(mRenderer, "Images/Coin.png", mLevelMap, direction);
	coinItem->SetPosition(x, y);

	mCoinsV.push_back(coinItem);
}

void GameScreenLevel1::CreateKoopa(FACING direction, float x, float y)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, direction);
	koopaCharacter->SetPosition(x, y);

	mKoopaV.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateGoomba(FACING direction, float x, float y)
{
	CharacterGoomba* goombaCharacter = new CharacterGoomba(mRenderer, "Images/Goomba.png", mLevelMap, direction);
	goombaCharacter->SetPosition(x, y);

	mGoombaV.push_back(goombaCharacter);
}

void GameScreenLevel1::PeriodicSpawning(float deltaTime)
{
	//countdown to spawn more left koopa;
	if (mSpawnKoopaTime1 > 0.0f)
	{
		mSpawnKoopaTime1 -= deltaTime;
	}
	else if (mSpawnKoopaTime1 <= 0.0f)
	{
		float randSpawn = rand() % 7 + 9;

		CreateKoopa(FACING_RIGHT, 50, 96);

		mSpawnKoopaTime1 = randSpawn;
	}

	//countdown to spawn more right koopa;
	if (mSpawnKoopaTime2 > 0.0f)
	{
		mSpawnKoopaTime2 -= deltaTime;
	}
	else if (mSpawnKoopaTime2 <= 0.0f)
	{
		float randSpawn = rand() % 7 + 9;

		CreateKoopa(FACING_LEFT, 464, 96);

		mSpawnKoopaTime2 = randSpawn;
	}

	//countdown to spawn more goombas;
	if (mSpawnGoombaTime > 0.0f)
	{
		mSpawnGoombaTime -= deltaTime;
	}
	else if (mSpawnGoombaTime <= 0.0f)
	{
		float randSpawn = rand() % 6 + 10;
		CreateGoomba(FACING_LEFT, 440, 402);

		mSpawnGoombaTime = randSpawn;
	}

	//countdown to spawn more coins;
	if (mCoinsV.size() <= 0)
	{
		if (mSpawnCoinTime > 0.0f)
		{
			mSpawnCoinTime -= deltaTime;
		}
		else if (mSpawnCoinTime <= 0.0f)
		{
			int randSpawn = rand() % 2;

			if (randSpawn == 0)
			{
				CreateCoin(FACING_RIGHT, 262, 182);
			}
			else if (randSpawn == 1)
			{
				CreateCoin(FACING_RIGHT, 262, 420);
			}

			mSpawnCoinTime = 15.0f;
		}
	}
}

void GameScreenLevel1::SpawnStage()
{
	mLevelMap = new LevelMap();
	mLevelMap->LoadFromFile("Levels/Level1.txt");
} 

bool GameScreenLevel1::SetUpLevel()
{
	SpawnStage();

	mMarioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", mLevelMap);
	mMarioCharacter->SetPosition(100, 382);
	mMarioCharacter->SetPipeCollision(true);

	mScoreText = new Text2D(mRenderer, "Score:0", "Fonts/ARIAL.TTF", 200, 50);

	mBackgroundTexture = new Texture2D(mRenderer);

	mSpawnKoopaTime1 = 0.0f;
	mSpawnKoopaTime2 = 0.0f;
	mSpawnGoombaTime = 0.0f;
	mSpawnCoinTime = 0.0f;

	mPowBlock = new PowBlock(mRenderer,"Images/PowBlock.png", mLevelMap);
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	mPowBlockSE = new SoundEffect();
	mPowBlockSE->LoadFromFile("Music/Clang_SE.wav");

	mCoinCollectedSE = new SoundEffect();
	mCoinCollectedSE->LoadFromFile("Music/CoinCollected.wav");

	mBackgroundMusic = new SoundEffect();
	mBackgroundMusic->LoadFromFile("Music/Mario_Background.wav");
	mBackgroundMusic->Play(0, -1);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (int i = 0; i < mKoopaV.size(); i++)
	{
		mKoopaV.at(i)->TakeDamage();
	}

	for (int i = 0; i < mGoombaV.size(); i++)
	{
		mGoombaV.at(i)->TakeDamage();
	}
}