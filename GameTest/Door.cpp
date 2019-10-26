#include "stdafx.h"
#include "Door.h"

#include "app.h"

Door::Door(float xCenterPos, float yCenterPos, float width, float height) :
	m_isPlayingEndGame(false), m_rColor(0.0f), m_gColor(1.0f), m_bColor(1.0f)
{
	m_box.x1 = xCenterPos - width*0.5f;
	m_box.x2 = xCenterPos + width*0.5f;
	m_box.y1 = yCenterPos - height*0.5f;
	m_box.y2 = yCenterPos + height*0.5f;
}

Door::~Door()
{
}

void Door::Update(float deltaTime)
{
	if (!m_isPlayingEndGame)
	{
		return;
	}

	float colorDelta = 0.2f * deltaTime /1000.0f;

	m_rColor = fmodf(m_rColor+colorDelta, 1.f);
	m_gColor = fmodf(m_gColor+colorDelta, 1.f);
	m_bColor = fmodf(m_bColor+colorDelta, 1.f);
}

void Door::Render()
{
	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	App::DrawLine(m_box.x1, m_box.y1, m_box.x2, m_box.y1, m_rColor, m_gColor, m_bColor);
	App::DrawLine(m_box.x2, m_box.y1, m_box.x2, m_box.y2, m_rColor, m_gColor, m_bColor);
	App::DrawLine(m_box.x2, m_box.y2, m_box.x1, m_box.y2, m_rColor, m_gColor, m_bColor);
	App::DrawLine(m_box.x1, m_box.y2, m_box.x1, m_box.y1, m_rColor, m_gColor, m_bColor);
}

bool Door::IsInside(float xPos, float yPos)
{
	if (xPos > m_box.x1 && xPos < m_box.x2)
	{
		if (yPos > m_box.y1 && yPos < m_box.y2)
		{
			return true;
		}
	}

	return false;
}

void Door::StartEndGame()
{
	m_isPlayingEndGame = true;

	m_rColor = 0.25f;
	m_gColor = 0.5f;
	m_bColor = 0.75f;
}
