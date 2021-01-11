#include "GravityGuy.h"

GravityGuy::GravityGuy(SDL_Renderer* renderer, char* imagePath, FACING startFacing, int playerNum) : GameObject(renderer, imagePath)
{
	mCharacterState = ALIVE;
	mGravityDir = SOUTH;

	mLaunchSE = new SoundEffect();
	mLaunchSE->LoadFromFile("Music/Launch.wav");

	mPlayerNum = playerNum;

	mFacingDirection = startFacing;

	mSingleSpriteWidth = mTexture->GetWidth() / 8;
	mSingleSpriteHeight = mTexture->GetHeight();

	mBlockUp = false;
	mBlockDown = false;
	mTouchedUp = false;
	mTouchedDown = false;
}

GravityGuy::~GravityGuy()
{
	mLaunchSE->CleanChannel();
	delete mLaunchSE;
	mLaunchSE = NULL;
}

void GravityGuy::Update(float deltaTime, SDL_Event e)
{
	CheckKeyboard(deltaTime, e);

	if (!mBlockRight)
	{
		mFramesWaited -= deltaTime;
		if (mFramesWaited <= 0.0f)
		{
			if (mPosition.x + mSingleSpriteWidth < SCREEN_WIDTH / 2
				&& mSetToCenter)
			{
				mPosition.x += 0.035f;
			}
			else
			{
				mFramesWaited = 5;
				mSetToCenter = false;
			}
		}
	}
	else
	{
		mFramesWaited = 5;
	}

	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY_SMALL;

		mCurrentFrame++;

		if (mCurrentFrame > 7)
		{
			mCurrentFrame = 0;
		}
	}

	AddGravity(deltaTime);
	GameObject::Update(deltaTime, e);
}

void GravityGuy::Render()
{
	SDL_Rect portionOfSpriteSheet = { mSingleSpriteWidth*mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mGravityDir == SOUTH)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE, 0);
	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_VERTICAL, 0);
	}				
}

void GravityGuy::CheckKeyboard(float deltaTime, SDL_Event e)
{
	if (mPlayerNum == 1)
	{
		switch (e.type)
		{
			//KeyDown
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_r:
				if (mGravityDir == SOUTH && mTouchedDown)
				{
					mLaunchSE->Play(1, 0);

					//flipped gravity
					SetGravity(NORTH);
				}
				else if (mGravityDir == NORTH && mTouchedUp)
				{
					mLaunchSE->Play(1, 0);
					
					//normal gravity
					SetGravity(SOUTH);
				}
				break;
			}
			break;
		}
	}
	else if (mPlayerNum == 2)
	{
		switch (e.type)
		{
			//KeyDown
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_p:
				if (mGravityDir == SOUTH && mTouchedDown)
				{
					mLaunchSE->Play(1, 0);

					//flipped gravity
					SetGravity(NORTH);
				}
				else if (mGravityDir == NORTH && mTouchedUp)
				{
					mLaunchSE->Play(1, 0);

					//normal gravity
					SetGravity(SOUTH);
				}
				break;
			}
			break;
		}
	}
}

void GravityGuy::SetTouchedBarrier(bool touched, int direction)
{
	switch (direction)
	{
	case 1:
		mTouchedDown = touched;
		mTouchedUp = !touched;
		break;
	case 2:
		mTouchedUp = touched;
		mTouchedDown = !touched;
		break;
	}
}

void GravityGuy::SetBlocked(bool blocked, int direction)
{
	switch (direction)
	{
	case 0:
		mBlockDown = blocked;
		mBlockUp = blocked;
		break;
	case 1:
		mBlockDown = blocked;
		break;
	case 2:
		mBlockUp = blocked;
		break;
	case 3:
		mBlockRight = blocked;
		break;
	}
}

void GravityGuy::AddGravity(float deltaTime)
{
	switch (mGravityDir)
	{
	case 0:
		if (!mBlockUp)
		{
			mPosition.y += GRAVITY * deltaTime;
			mBlockRight = false;
		}
		break;
	case 1:
		if (!mBlockDown)
		{
			mPosition.y -= GRAVITY * deltaTime;
			mBlockRight = false;
		}
		break;
	}
}

void GravityGuy::SetState(CHARACTER_STATE state)
{
	mCharacterState = state;
}

void GravityGuy::SetGravity(GRAVITY_DIR gravityDir)
{
	mGravityDir = gravityDir;
}

void GravityGuy::SetToCenter(bool ready)
{
	mSetToCenter = ready;
}

const int GravityGuy::GetPlayerNum()
{
	return mPlayerNum;
}

const CHARACTER_STATE GravityGuy::GetState()
{
	return mCharacterState;
}

Rect2D const GravityGuy::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
}