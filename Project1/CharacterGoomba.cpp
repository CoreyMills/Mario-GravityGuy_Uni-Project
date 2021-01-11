#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, char* imagePath, LevelMap* map, FACING startFacing) : Character(renderer, imagePath, map)
{
	mFacingDirection = startFacing;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterGoomba::~CharacterGoomba()
{
}

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	if (mCharacterState == INJURED)
	{
		mMovingRight = false;
		mMovingLeft = false;
	}
	else if (mCharacterState == ALIVE)
	{
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else
		{
			mMovingRight = true;
			mMovingLeft = false;
		}

		mFrameDelay -= deltaTime;

		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = ANIMATION_DELAY;

			mCurrentFrame++;

			if (mCurrentFrame > 1)
			{
				mCurrentFrame = 0;
			}
		}
	}
}

void CharacterGoomba::TakeDamage()
{
	Jump(INITIAL_JUMP_FORCE_SMALL);
	mCharacterState = INJURED;

	//allow object to pass through background
	SetBackgroundCollision(false);
}

Rect2D const CharacterGoomba::GetKillingRect()
{
	return Rect2D(mPosition.x + (mSingleSpriteWidth / 4), mPosition.y - (mSingleSpriteWidth / 8), mSingleSpriteWidth / 2, mSingleSpriteHeight / 4);
}