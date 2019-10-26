#include "stdafx.h"
#include "LaserWall.h"
#include "app.h"



LaserWall::LaserWall(float x1, float x2, float y1, float y2)
{
	float minX = x1 < x2 ? x1 : x2;
	float maxX = x1 > x2 ? x1 : x2;
	float minY = y1 < y2 ? y1 : y2;
	float maxY = y1 > y2 ? y1 : y2;

	m_box.x1 = minX;
	m_box.x2 = maxX;
	m_box.y1 = minY;
	m_box.y2 = maxY;
}

void LaserWall::Render()
{
	App::DrawLine(m_box.x1, m_box.y1, m_box.x2, m_box.y2, 1.0f, 0.0f, 0.0f);
}
