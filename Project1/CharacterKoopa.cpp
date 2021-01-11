#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, char* imagePath, LevelMap* map, FACING startFacing) : Character(renderer, imagePath, map)
{
	mFacingDirection = startFacing;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!mInjured)
	{
		if (mPosition.y < 370)
		{
			if (mPosition.x + mSingleSpriteWidth < 0 + mSingleSpriteWidth)
			{
				mFacingDirection = FACING_RIGHT;
			}
			else if (mPosition.x > SCREEN_WIDTH - mSingleSpriteWidth)
			{
				mFacingDirection = FACING_LEFT;
			}
		}

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
	}
	else
	{
		mMovingLeft = false;
		mMovingRight = false;

		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0f)
		{
			FlipRightwayUp();
		}
	}
}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE, 0);
	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL, 0);
	}
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_DURATION;
	Jump(INITIAL_JUMP_FORCE_SMALL);
}

void CharacterKoopa::FlipRightwayUp()
{
	mInjured = false;
	Jump(INITIAL_JUMP_FORCE_SMALL);
}

bool CharacterKoopa::CheckInjured()
{
	return mInjured;
}