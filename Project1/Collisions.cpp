#include "Collisions.h"

//Initialise the instance to null
Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{
}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance()
{
	if (mInstance == NULL)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Circle(Capsule2D capsule1, Capsule2D capsule2)
{
	Vector2D vec = Vector2D((capsule1.x - capsule2.x),
		(capsule1.y - capsule2.y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combinedDistance = (capsule1.radius + capsule2.radius);

	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if ((rect1.x < rect2.x + rect2.width) &&
		(rect2.x < rect1.x + rect1.width) &&
		(rect1.y < rect2.y + rect2.height) &&
		(rect2.y < rect1.y + rect1.height))
	{
		return true;
	}

	return false;
}

int Collisions::Collision(GameObject* movingObj, Rect2D* immovableRect)
{
	Rect2D* movingRect = new Rect2D(movingObj->GetCollisionBox());

	//1D point centres
	float immovableXCentre = (immovableRect->x + (immovableRect->width / 2));
	float immovableYCentre = (immovableRect->y + (immovableRect->height / 2));
	float movingXCentre = (movingRect->x + (movingRect->width / 2));
	float movingYCentre = (movingRect->y + (movingRect->height / 2));

	//2D point centres
	//X centers
	Vector2D immovableNCentre; immovableNCentre.x = immovableXCentre; immovableNCentre.y = immovableRect->y;
	Vector2D immovableSCentre; immovableSCentre.x = immovableXCentre; immovableSCentre.y = immovableRect->y + immovableRect->height;
	//Y centres
	Vector2D immovableWCentre; immovableWCentre.x = immovableRect->x; immovableWCentre.y = immovableYCentre;
	Vector2D immovableECentre; immovableECentre.x = immovableRect->x + immovableRect->width; immovableECentre.y = immovableYCentre;
	//pacman centre
	Vector2D movingCentre; movingCentre.x = movingXCentre; movingCentre.y = movingYCentre;

	Vector2D distX;
	float distXFloat;
	Vector2D distY;
	float distYFloat;

	bool top;
	bool left;

	//horizontal
	if (movingXCentre < immovableXCentre)
	{
		distXFloat = Distance(movingCentre, immovableWCentre);
		left = true;
	}
	else
	{
		distXFloat = Distance(movingCentre, immovableECentre);
		left = false;
	}

	//vertical
	if (movingYCentre < immovableYCentre)
	{
		distYFloat = Distance(movingCentre, immovableNCentre);
		top = true;
	}
	else
	{
		distYFloat = Distance(movingCentre, immovableSCentre);
		top = false;
	}

	//find specific side
	if (distYFloat < distXFloat)
	{
		//movingObj on top
		if (top)
		{
			movingObj->SetPosition(movingObj->GetPosition().x, immovableRect->y - movingRect->height);
			return 1;
		}
		else
		{
			movingObj->SetPosition(movingObj->GetPosition().x, immovableRect->y + immovableRect->height);
			return 2;
		}
	}
	else
	{
		//movingObj on left
		if (left)
		{
			movingObj->SetPosition(immovableRect->x - movingRect->width - 1, movingObj->GetPosition().y);
			return 3;
		}
		else
		{
			movingObj->SetPosition(immovableRect->x + immovableRect->width + 1, movingObj->GetPosition().y);
			return 4;
		}
	}
}

float Collisions::Distance(Vector2D rect1, Vector2D rect2)
{
	return sqrt(pow(rect1.x - rect2.x, 2) + pow(rect1.y - rect2.y, 2));
}