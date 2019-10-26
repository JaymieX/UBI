#pragma once


struct AABB
{
	float x1;
	float x2;
	float y1;
	float y2;
};



bool areColliding(const AABB& box1, const AABB& box2);

