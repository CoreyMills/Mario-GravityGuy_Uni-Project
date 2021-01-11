#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include "Texture2D.h"
#include "Commons.h"
#include "LevelMap.h"
#include "GameScreen.h"
#include "SoundEffect.h"
#include "Collisions.h"
#include "Text2D.h"
#include "GravityGuy.h"

#include <vector>
#include <iostream>
#include <sstream>

class Texture2D;

class GameScreenLevel2 : GameScreen
{
private:
	Rect2D * mCamera;
	float mCameraTravelledBy;

	std::vector<GravityGuy*> mPlayerVArray;
	std::vector<GameObject*> mBarrierVArray;
	std::vector<GameObject*> mCheckpointVArray;
	std::vector<GameObject*> mStageEndVArray;
	std::vector<GameObject*> mLevelEndVArray;
	std::vector<LevelMap*> mStageVArray;

	Text2D* mStageText;

	int mStagesToComplete;
	int mCurrentStage;
	int mLevelWidth;
	int mLevelHeight;

	bool mMultiplayer;

	//NOTE:: 0 = checkpoint, 1 = stageEnd, 2 = levelEnd, 3 = barrier
	void SpawnEmptyGameObject(float x, float y, int vArrayChosen);
	void SpawnStage();
	void CheckCollisions(GravityGuy* player);
	void CheckCameraView();

	bool CheckOutOfBounds(GameObject* object, Rect2D* boundaryBox);
	bool SetUpLevel();

public:
	GameScreenLevel2(SDL_Renderer* renderer, SCREENS thisScreen, GAME_STATUS mCurrentGameStatus, bool multiplayer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
#endif