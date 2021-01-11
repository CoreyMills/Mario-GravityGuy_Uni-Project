#include "Item.h"

Item::Item(SDL_Renderer* renderer, char* imagePath, LevelMap* map) : GameObject(renderer, imagePath, map)
{
	mItemState = NOT_FOUND;
}

Item::~Item()
{
}

void Item::SetState(ITEM_STATE itemState)
{
	mItemState = itemState;
}

bool const Item::GetState()
{
	return mItemState;
}