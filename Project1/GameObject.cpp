#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, char* imagePath, LevelMap* map)
{
	mCurrentFrame = 0;

	mRadius = 15.0f;

	mPosition.x = 0.0f;
	mPosition.y = 0.0f;

	mFacingDirection = FACING_RIGHT;

	mCurrentLevelMap = map;

	mRenderer = renderer;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	if (mTexture == NULL)
	{
		std::cout << "Failed to load texture: " << imagePath << std::endl;
		return;
	}

	mSingleSpriteWidth = mTexture->GetWidth();
	mSingleSpriteHeight = mTexture->GetHeight();
}

GameObject::GameObject(SDL_Renderer* renderer, char* imagePath)
{
	mCurrentFrame = 0;

	mRadius = 15.0f;

	mPosition.x = 0.0f;
	mPosition.y = 0.0f;

	mFacingDirection = FACING_RIGHT;

	mRenderer = renderer;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	if (mTexture == NULL)
	{
		std::cout << "Failed to load texture: " << imagePath << std::endl;
		return;
	}

	mSingleSpriteWidth = mTexture->GetWidth();
	mSingleSpriteHeight = mTexture->GetHeight();
}

GameObject::~GameObject()
{
	mRenderer = NULL;

	delete mCurrentLevelMap;
	mCurrentLevelMap = NULL;

	delete mTexture;
	mTexture = NULL;
}

void GameObject::Update(float deltaTime, SDL_Event e)
{
}

void GameObject::Render()
{
	SDL_Rect portionOfSpriteSheet = { mSingleSpriteWidth*mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };
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

void GameObject::SetPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}

Vector2D const GameObject::GetPosition()
{
	return mPosition;
}

Capsule2D const GameObject::GetCollisionCircle()
{
	return Capsule2D(mPosition.x, mPosition.y, mRadius);
}

Rect2D const GameObject::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
}