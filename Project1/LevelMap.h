#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "Constants.h"
#include "Commons.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

class LevelMap
{
private:
	int** mMap;

	int mMapWidth;
	int mMapHeight;

public:
	LevelMap();
	~LevelMap();

	void LoadFromFile(std::string fileName);
	void ChangeTileAt(unsigned int w, unsigned int h, unsigned int newValue);

	const int GetTileValue(unsigned int w, unsigned int h);
	const int GetTilePosW(unsigned int w, unsigned int h);
	const int GetTilePosH(unsigned int w, unsigned int h);
	Rect2D* GetTileRect2D(unsigned int w, unsigned int h);
	const int GetMapWidth();
	const int GetMapHeight();
};
#endif