#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"

class Character: public GameObject
{
protected:
	CHARACTER_STATE mCharacterState;

	bool mBackgroundCollision;
	bool mPipeCollision;

	bool mBlockLeftMove;
	bool mBlockRightMove;
	bool mBlockFalling;
	bool mBlockJump;

	bool mSWCheck;
	bool mSECheck;

	bool mMovingLeft;
	bool mMovingRight;

	bool mJumping;
	float mJumpForce;

	void CheckCollisions(float deltaTime);

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	void AddGravity(float deltaTime);
	void Jump(float jumpForce);

public:
	Character(SDL_Renderer* renderer, char* imagePath, LevelMap* map);
	~Character();

	virtual void Update(float deltaTime, SDL_Event e);
	void CancelJump();

	//NOTE: 1 = up, 2 = right, 3 = down, 4 = left
	void SetBlocked(bool blocked, int direction);
	void SetState(CHARACTER_STATE state);
	void SetBackgroundCollision(bool backgroundCollision);
	void SetPipeCollision(bool pipeCollision);

	const CHARACTER_STATE GetState();
	const bool GetJumping();
};
#endif