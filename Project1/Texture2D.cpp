#include "Texture2D.h"

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;

	mWidth = 512;
	mHeight = 416;
}

Texture2D::~Texture2D()
{
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	Free();
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		if (mTexture != NULL)
		{
			mWidth = pSurface->w;
			mHeight = pSurface->h;
		}
		else
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(pSurface);
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError() << std::endl;
	}

	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f)
{
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}