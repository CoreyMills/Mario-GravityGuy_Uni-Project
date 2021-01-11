#pragma once
#ifndef _ITEM_H
#define _ITEM_H

#include "GameObject.h"

class Item : public GameObject
{
protected:
	ITEM_STATE mItemState;

public:
	Item(SDL_Renderer* renderer, char* imagePath, LevelMap* map);
	~Item();

	void SetState(ITEM_STATE itemState);

	bool const GetState();
};
#endif