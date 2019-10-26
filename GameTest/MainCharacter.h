#pragma once

#include "AABB.h"
class CSimpleSprite;


class MainCharacter
{
public:	
	MainCharacter();
	~MainCharacter();

	void Update(float deltaTime);
	void Render();
	void DebugRender();

	void StartEndGame();

	void GetCenterPos(float& x, float& y);
	const AABB& GetAABB() const { return m_box; };

private:
	enum
	{
		ANIM_FORWARDS,
		ANIM_BACKWARDS,
		ANIM_LEFT,
		ANIM_RIGHT,
	};

	CSimpleSprite* m_sprite;
	bool m_isPlayingEndGame;
	bool m_debugRenderOn;

	AABB m_box;


	void UpdateAABB();
};

