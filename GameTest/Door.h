#pragma once

#include "AABB.h"

class Door
{
public:
	Door(float xCenterPos, float yCenterPos, float width, float height);
	~Door();

	void Update(float deltaTime);
	void Render();

	void StartEndGame();

	bool IsInside(float xPos, float yPos);
	const AABB& GetAABB() const { return m_box; };

private:
	AABB  m_box;

	float m_rColor;
	float m_gColor;
	float m_bColor;

	bool m_isPlayingEndGame;
};

