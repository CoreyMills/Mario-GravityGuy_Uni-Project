#include "LevelMap.h"

LevelMap::LevelMap()
{
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < mMapHeight; i++)
	{
		delete mMap[i];
	}
	delete []mMap;
}

//0 = Empty Area, 1 = Blocked Area, 2 = Blocked to Player only, 3 = CheckPoint, 4 = Stage Ending
void LevelMap::LoadFromFile(std::string fileName)
{
	std::vector<std::string>* lines = new std::vector<std::string>();
	std::fstream stream;
	std::stringstream ss;
	ss << fileName;
	stream.open(ss.str(), std::fstream::in);

	char* line = new char[256];
	stream.getline(line, 256);
	std::string* sline = new std::string(line);
	mMapWidth = sline->size();

	while (!stream.eof())
	{
		lines->push_back(*sline);
		if (sline->size() != mMapWidth)
		{
			std::cout << "Bad Level Load\n";
		}

		stream.getline(line, 256);
		delete sline;
		sline = new std::string(line);
	}

	delete[] line;
	delete sline;

	mMapHeight = lines->size();

	mMap = new int*[mMapHeight];

	for (unsigned int i = 0; i < mMapHeight; i++)
	{
		mMap[i] = new int[mMapWidth];
	}

	for (unsigned int i = 0; i < mMapHeight; i++)
	{
		for (unsigned int j = 0; j < mMapWidth; j++)
		{
			mMap[i][j] = lines->at(i)[j] - 48;
		}
	}

	delete lines;
}

void LevelMap::ChangeTileAt(unsigned int w, unsigned int h, unsigned int newValue)
{
	if (0 <= w && w <= mMapWidth &&
		0 <= h && h <= mMapHeight)
	{
		mMap[h][w] = newValue;
	}
}

const int LevelMap::GetTileValue(unsigned int w, unsigned int h)
{
	if (0 <= w && w <= mMapWidth &&
		0 <= h && h <= mMapHeight)
	{
		return mMap[h][w];
	}
	return 0;
}

const int LevelMap::GetTilePosW(unsigned int w, unsigned int h)
{
	if (0 <= w && w <= mMapWidth &&
		0 <= h && h <= mMapHeight)
	{
		return w;
	}
	return 0;
}

const int LevelMap::GetTilePosH(unsigned int w, unsigned int h)
{
	if (0 <= w && w <= mMapWidth &&
		0 <= h && h <= mMapHeight)
	{
		return h;
	}
	return 0;
}

Rect2D* LevelMap::GetTileRect2D(unsigned int w, unsigned int h)
{
	if (0 <= w && w <= mMapWidth &&
		0 <= h && h <= mMapHeight)
	{
		Rect2D* tempRect = new Rect2D(w * TILE_WIDTH, h * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
		return tempRect;
	}
	return 0;
}

const int LevelMap::GetMapWidth()
{
	return mMapWidth;
}

const int LevelMap::GetMapHeight()
{
	return mMapHeight;
}