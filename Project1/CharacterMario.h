#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include "SoundEffect.h"

class CharacterMario : public Character
{
private:
	SoundEffect* mJumpSE;

	bool mDamaged;
	float mFrameDelay;

	bool mProtected;
	float mProtectedTime;

	int mCoinsCollected;
	int mPoints;

public:
	CharacterMario(SDL_Renderer* renderer, char* imagePath, LevelMap* map);
	~CharacterMario();
	void Update(float deltaTime, SDL_Event e);

	void SetCoinsAmount(int coinsAmount);
	void SetPointsAmount(int pointsAmount);
	void SetDamaged(bool hit);
	void SetProtected(bool playerProtected);

	int GetCoinsAmount();
	int GetPointsAmount();
	bool CheckDamaged();
	bool CheckProtected();
};
#endif