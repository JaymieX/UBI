#include "stdafx.h"
#include "AABB.h"




bool areColliding(const AABB& box1, const AABB& box2)
{
	if (box1.x1 <= box2.x2 &&
		box1.x2 >= box2.x1 &&
		box1.y1 <= box2.y2 &&
		box1.y2 >= box2.y1)
		return true;
	return false;
}