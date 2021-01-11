#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, char* imagePath, LevelMap* map) : GameObject(renderer, imagePath, map)
{
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();

	mNumberOfHitsLeft = 3;
	mPosition = Vector2D(256, 320);
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;

	mCurrentLevelMap = NULL;
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		int left = mSingleSpriteWidth*(mNumberOfHitsLeft - 1);

		SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE, 0);
	}
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mCurrentLevelMap->ChangeTileAt(8, 10, 0);
	}
}

bool PowBlock::IsAvailable()
{
	if (mNumberOfHitsLeft > 0)
	{
		return true;
	}
	return false;
}

Rect2D const PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth() / 3, mTexture->GetHeight());
}