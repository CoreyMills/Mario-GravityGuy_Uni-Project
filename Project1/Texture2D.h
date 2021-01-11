#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include "SDL.h"
#include "Commons.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

class Texture2D
{
private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(string path);
	void Free();
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle);
	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
};
#endif