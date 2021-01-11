#include "Character.h"

Character::Character(SDL_Renderer* renderer, char* imagePath, LevelMap* map): GameObject(renderer, imagePath, map)
{
	mCharacterState = ALIVE;

	mBackgroundCollision = true;

	mMovingLeft = false;
	mMovingRight = false;

	mSWCheck = false;
	mSECheck = false;

	mBlockLeftMove = false;
	mBlockRightMove = false;
	mBlockFalling = true;
	mBlockJump = false;

	mJumping = false;
	mJumpForce = 0.1f;
}

Character::~Character()
{
}

void Character::Update(float deltaTime, SDL_Event e)
{
	GameObject::Update(deltaTime, e);

	if (mJumping)
	{
		mBlockLeftMove = false;
		mBlockRightMove = false;

		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
		mBlockRightMove = false;
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
		mBlockLeftMove = false;
	}

	CheckCollisions(deltaTime);
}

void Character::CheckCollisions(float deltaTime)
{
	if (mBackgroundCollision)
	{
		//Collision position vars
		int NWPos = (int)(mPosition.x) / TILE_WIDTH;
		int NEPos = (int)((mPosition.x + mSingleSpriteWidth) / TILE_WIDTH);
		int footPos = (int)(mPosition.y + mSingleSpriteHeight) / TILE_HEIGHT;

		if (mPipeCollision)
		{
			//check if left most side hits pipe
			if (mCurrentLevelMap->GetTileValue(NEPos, footPos - 1) == 2)
			{
				int tileX = mCurrentLevelMap->GetTilePosW(NEPos, footPos) * 32;
				int tileY = mCurrentLevelMap->GetTilePosH(NEPos, footPos) * 32;

				if ((mPosition.x + mTexture->GetWidth()) > tileX)
				{
					mPosition.x = tileX - 32;
					mBlockRightMove = true;
				}
			}

			//check if right most side hits pipe
			if (mCurrentLevelMap->GetTileValue(NWPos, footPos - 1) == 2)
			{
				int tileX = mCurrentLevelMap->GetTilePosW(NWPos, footPos) * 32;
				int tileY = mCurrentLevelMap->GetTilePosH(NWPos, footPos) * 32;

				if ((mPosition.x + mTexture->GetWidth()) > tileX)
				{
					mPosition.x = tileX + 32;
					mBlockLeftMove = true;
				}
			}
		}

		//check if left most side is hovering
		if (mCurrentLevelMap->GetTileValue(NWPos, footPos) == 0)
		{
			mSWCheck = true;
		}
		else
		{
			mSWCheck = false;
		}

		//check if right most side is hovering
		if (mCurrentLevelMap->GetTileValue(NEPos, footPos) == 0)
		{
			mSECheck = true;
		}
		else
		{
			mSECheck = false;
		}

		if (mSWCheck && mSECheck)
		{
			mBlockJump = true;
			mBlockFalling = false;
			AddGravity(deltaTime);
		}
		else
		{
			mBlockFalling = true;
			mBlockJump = false;
		}
	}
	else if (!mBackgroundCollision)
	{
		mBlockFalling = false;
		AddGravity(deltaTime);
	}
}

void Character::SetBackgroundCollision(bool backgroundCollision)
{
	mBackgroundCollision = backgroundCollision;
}

void Character::SetPipeCollision(bool pipeCollision)
{
	mPipeCollision = pipeCollision;
}

void Character::SetBlocked(bool blocked, int direction) 
{
	switch (direction)
	{
	case 1:
		mBlockJump = blocked;
		break;
	case 2:
		mBlockRightMove = blocked;
		break;
	case 3:
		mBlockFalling = blocked;
		break;
	case 4:
		mBlockLeftMove = blocked;
		break;
	}
}

void Character::Jump(float jumpForce)
{
	if (!mJumping && !mBlockJump)
	{
		mJumpForce = jumpForce;
		mJumping = true;
		mBlockJump = false;
	}
}

void Character::AddGravity(float deltaTime)
{
	if (!mBlockFalling)
	{
		mPosition.y += GRAVITY * deltaTime;
		mBlockJump = true;
	}
}

void Character::MoveLeft(float deltaTime)
{
	if (!mBlockLeftMove)
	{
		mFacingDirection = FACING_LEFT;
		mPosition.x -= MOVEMENT_SPEED * deltaTime;
	}
}

void Character::MoveRight(float deltaTime)
{
	if (!mBlockRightMove)
	{
		mFacingDirection = FACING_RIGHT;
		mPosition.x += MOVEMENT_SPEED * deltaTime;
	}
}

void Character::CancelJump()
{
	mJumpForce = 0;
	mBlockJump = true;
}

void Character::SetState(CHARACTER_STATE state)
{
	mCharacterState = state;
}

const CHARACTER_STATE Character::GetState()
{
	return mCharacterState;
}

const bool Character::GetJumping()
{
	return mJumping;
}