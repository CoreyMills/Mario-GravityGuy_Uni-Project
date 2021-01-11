#pragma once
#ifndef _TEXT2D_H
#define _TEXT2D_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"

//#include <iostream>

class Text2D
{
private:
	SDL_Renderer* mRenderer;
	SDL_Surface* mSurface;
	TTF_Font* mFont;
	SDL_Texture* mMessage;
	SDL_Rect mMessageRect;
	SDL_Color mColor;

	Vector2D mPosition;

	char* mText;

	int mWidth, mHeight;

public:
	Text2D(SDL_Renderer* renderer, char* string, char* path, float width, float height);
	~Text2D();

	void Update();
	void Render();

	Vector2D const GetPosition();
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	void SetPosition(float x, float y);
	void SetText(char* text);
	void SetTextColor(Uint8 r, Uint8 g, Uint8 b);
};
#endif