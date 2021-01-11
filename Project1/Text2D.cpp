#include "Text2D.h"
#include <SDL_image.h>

Text2D::Text2D(SDL_Renderer* renderer, char* screenText, char* path, float width, float height)
{
	mRenderer = renderer;

	mText = screenText;

	mPosition.x = 0;
	mPosition.y = 0;

	mWidth = width;
	mHeight = height;

	mColor = { 255, 255, 255 };
	mMessageRect = { (int)mPosition.x, (int)mPosition.y, mWidth, mHeight };

	mFont = TTF_OpenFont(path, 30);
}

Text2D::~Text2D()
{
	mRenderer = NULL;

	delete mSurface;
	mSurface = NULL;

	delete mFont;
	mFont = NULL;

	delete mMessage;
	mMessage = NULL;

	delete mText;
	mText = NULL;
}

void Text2D::Update()
{
	mSurface = TTF_RenderText_Solid(mFont, mText, mColor);

	mMessage = SDL_CreateTextureFromSurface(mRenderer, mSurface);

	SDL_FreeSurface(mSurface);
}

void Text2D::Render()
{
	SDL_RenderCopy(mRenderer, mMessage, NULL, &mMessageRect);
}

Vector2D const Text2D::GetPosition()
{
	return mPosition;
}

void Text2D::SetPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Text2D::SetText(char* text)
{
	mText = text;
}

void Text2D::SetTextColor(Uint8 r, Uint8 g, Uint8 b)
{
	mColor = { r, g, b };
}