#pragma once
#ifndef _ITEMCOIN_H
#define _ITEMCOIN_H

#include "Item.h"
#include "Commons.h"

class ItemCoin : public Item
{
private:
	float mFrameDelay;

public:
	ItemCoin(SDL_Renderer* renderer, char* imagePath, LevelMap* map, FACING startFacing);
	~ItemCoin();

	void Update(float deltaTime, SDL_Event e);
};
#endif