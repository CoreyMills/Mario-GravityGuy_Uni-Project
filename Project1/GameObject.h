#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "SDL.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>

class GameObject
{
protected:
	LevelMap* mCurrentLevelMap;

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	FACING mFacingDirection;

	float mRadius;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mCurrentFrame;

public:
	GameObject(SDL_Renderer* renderer, char* imagePath, LevelMap* map);
	GameObject(SDL_Renderer* renderer, char* imagePath);
	~GameObject();

	void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(float x, float y);

	Vector2D const GetPosition();
	Capsule2D const GetCollisionCircle();
	virtual Rect2D const GetCollisionBox();
};
#endif