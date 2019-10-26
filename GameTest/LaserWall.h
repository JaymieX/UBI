#pragma once

#include "AABB.h"

class LaserWall
{
public:
	LaserWall(float x1, float x2, float y1, float y2);
	~LaserWall() {};

	void Render();

	const AABB& GetAABB() const { return m_box; };

private:
	AABB  m_box;
};
