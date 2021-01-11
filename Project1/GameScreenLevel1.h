#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "Texture2D.h"
#include "Commons.h"
#include "LevelMap.h"
#include "GameScreen.h"

#include "Character.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterGoomba.h"
#include "SoundEffect.h"
#include "Collisions.h"
#include "PowBlock.h"

#include "ItemCoin.h"
#include "Text2D.h"

#include <vector>
#include <iostream>

class GameScreenLevel1 : GameScreen
{
private:
	std::vector<CharacterKoopa*> mKoopaV;
	std::vector<CharacterGoomba*> mGoombaV;
	std::vector<ItemCoin*> mCoinsV;
	
	CharacterMario* mMarioCharacter;
	PowBlock* mPowBlock;

	LevelMap* mLevelMap;

	SoundEffect* mPowBlockSE;
	SoundEffect* mCoinCollectedSE;

	Text2D* mScoreText;

	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;

	float mSpawnKoopaTime1;
	float mSpawnKoopaTime2;
	float mSpawnGoombaTime;
	float mSpawnCoinTime;

	void CreateKoopa(FACING direction, float x, float y);
	void CreateGoomba(FACING direction, float x, float y);
	void CreateCoin(FACING direction, float x, float y);
	void PeriodicSpawning(float deltaTime);
	void UpdatePowBlock();
	void UpdateCoins(float deltaTime, SDL_Event e);
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CollectCoins(int coinsAmount, int coinIndex);
	void DeleteDeadCharacters();
	void DoScreenShake();
	void SpawnStage();

	bool SetUpLevel();

public:
	GameScreenLevel1(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS mCurrentGameStatus);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
#endif