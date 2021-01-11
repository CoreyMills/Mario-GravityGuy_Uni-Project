#pragma once
#ifndef _CHARACTERGOOMBA_H
#define _CHARACTERGOOMBA_H

#include "Character.h"
#include "Commons.h"

class CharacterGoomba : public Character
{
private:
	float mFrameDelay;

public:
	CharacterGoomba(SDL_Renderer* renderer, char* imagePath, LevelMap* map, FACING startFacing);
	~CharacterGoomba();
	void Update(float deltaTime, SDL_Event e);

	void TakeDamage();

	Rect2D const GetKillingRect();
};
#endif