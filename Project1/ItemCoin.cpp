#include "ItemCoin.h"

ItemCoin::ItemCoin(SDL_Renderer* renderer, char* imagePath, LevelMap* map, FACING startFacing) : Item(renderer, imagePath, map)
{
	mFacingDirection = startFacing;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
}

ItemCoin::~ItemCoin()
{
}

void ItemCoin::Update(float deltaTime, SDL_Event e)
{
	mFrameDelay -= deltaTime;

	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY;

		mCurrentFrame++;

		if (mCurrentFrame > 2)
		{
			mCurrentFrame = 0;
		}
	}
}