#pragma once

#ifndef _GRAVITYGUY_H
#define _GRAVITYGUY_H

#include "GameObject.h"
#include "SoundEffect.h"

class GravityGuy: public GameObject
{
private:
	CHARACTER_STATE mCharacterState;
	GRAVITY_DIR mGravityDir;

	SoundEffect* mLaunchSE;

	int mPlayerNum;

	float mFrameDelay;

	bool mBlockUp;
	bool mBlockDown;
	bool mTouchedUp;
	bool mTouchedDown;

	bool mBlockRight;
	bool mSetToCenter;
	float mFramesWaited;

	void CheckKeyboard(float deltaTime, SDL_Event e);

	void AddGravity(float deltaTime);

public:
	GravityGuy(SDL_Renderer* renderer, char* imagePath, FACING startFacing, int playerNum);
	~GravityGuy();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	//NOTE: 0 = reset, 1 = down, 2 = up, 3 = right
	void SetBlocked(bool blocked, int direction);

	/*NOTE: 1 = down, 2 = up
	(Method Sets other direction to opposite state)*/
	void SetTouchedBarrier(bool blocked, int direction);
	void SetState(CHARACTER_STATE state);
	void SetToCenter(bool ready);
	void SetGravity(GRAVITY_DIR gravityDir);

	const CHARACTER_STATE GetState();
	Rect2D const GetCollisionBox();
	const int GetPlayerNum();
};
#endif