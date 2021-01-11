#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, char* imagePath, LevelMap* map) : Character(renderer, imagePath, map)
{
	mJumpSE = new SoundEffect();
	mJumpSE->LoadFromFile("Music/Jump.wav");

	mSingleSpriteWidth = mTexture->GetWidth() / 7;
	mSingleSpriteHeight = mTexture->GetHeight();

	mDamaged = false;
	mProtectedTime = 3;

	mPoints = 0;
}

CharacterMario::~CharacterMario()
{
	mJumpSE->CleanChannel();
	delete mJumpSE;
	mJumpSE = NULL;
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	if (mDamaged && mCurrentFrame < 6)
	{
		mFrameDelay -= deltaTime;

		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = ANIMATION_DELAY_SMALL;

			mCurrentFrame++;
		}
	}

	if (mProtected)
	{
		mProtectedTime -= deltaTime;
		if (mProtectedTime <= 0.0f)
		{
			mProtected = false;
		}
	}

	switch (e.type)
	{
		//KeyDown
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		case SDLK_d:
			mMovingRight = true;
			mMovingLeft = false;
			break;
		case SDLK_r:
			if (!mBlockJump && mBlockFalling)
			{
				mJumpSE->Play(1, 0);
			}

			Jump(INITIAL_JUMP_FORCE);
			break;
		}
		break;
		//KeyUp
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		}
	}

	Character::Update(deltaTime, e);
}

void CharacterMario::SetCoinsAmount(int coinsAmount)
{
	mCoinsCollected = coinsAmount;
}

void CharacterMario::SetPointsAmount(int pointsAmount)
{
	mPoints = pointsAmount;
}

void CharacterMario::SetDamaged(bool hit)
{
	mDamaged = hit;
}

void CharacterMario::SetProtected(bool playerProtected)
{
	mProtected = playerProtected;
}

int CharacterMario::GetCoinsAmount()
{
	return mCoinsCollected;
}

int CharacterMario::GetPointsAmount()
{
	return mPoints;
}

bool CharacterMario::CheckDamaged()
{
	return mDamaged;
}

bool CharacterMario::CheckProtected()
{
	return mProtected;
}