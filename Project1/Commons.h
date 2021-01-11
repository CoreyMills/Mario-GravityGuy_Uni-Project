#pragma once

#ifndef _COMMONS_H
#define _COMMONS_H

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D
{
	float x, y, width, height;

	Rect2D()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	Rect2D(float xPos, float yPos, float tempWidth, float tempHeight)
	{
		x = xPos;
		y = yPos;
		width = tempWidth;
		height = tempHeight;
	}
};

struct Capsule2D
{
	float x, y, radius;

	Capsule2D(float xPos, float yPos, float radius)
	{
		x = xPos;
		y = yPos;
		this->radius = radius;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum CHARACTER_STATE
{
	ALIVE = 0,
	INJURED,
	DEAD
};

enum ITEM_STATE
{
	NOT_FOUND = 0,
	FOUND,
	USED
};

enum GRAVITY_DIR
{
	SOUTH = 0,
	NORTH
};

enum GAME_STATUS
{
	RUNNING = 0,
	PLAYER1_WON,
	PLAYER2_WON,
	ALL_PLAYERS_WON,
	ALL_PLAYERS_LOST,
	HIGHSCORES,
	QUIT
};
#endif