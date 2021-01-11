#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"
#include "Commons.h"

class CharacterKoopa : public Character
{
private:
	bool mInjured;
	float mInjuredTime;

	void FlipRightwayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, char* imagePath, LevelMap* map, FACING startFacing);
	~CharacterKoopa();
	void Update(float deltaTime, SDL_Event e);
	void Render();

	void TakeDamage();
	bool CheckInjured();
};
#endif