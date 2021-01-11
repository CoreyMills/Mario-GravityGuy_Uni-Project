#pragma once
#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include "Commons.h"
#include "Character.h"

class Collisions
{
private:
	Collisions();

	static Collisions* mInstance;

public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Capsule2D capsule1, Capsule2D capsule2);
	bool Box(Rect2D rect1, Rect2D rect2);
	
	//NOTE: 1 = up, 2 = down, 3 = left, 4 = right
	int Collision(GameObject* movingObj, Rect2D* immovableObj);
	float Distance(Vector2D rect1, Vector2D rect2);
};
#endif