#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include "SDL.h"
#include "Commons.h"
#include "LevelMap.h"
#include "GameObject.h"

class PowBlock: public GameObject
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumberOfHitsLeft;

public:
	PowBlock(SDL_Renderer* renderer, char* imagePath, LevelMap* map);
	~PowBlock();

	void Render();
	void TakeAHit();

	bool IsAvailable();
	Rect2D const GetCollisionBox();
};
#endif _POWBLOCK_H