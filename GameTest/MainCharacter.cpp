#include "stdafx.h"
#include "MainCharacter.h"

#include "app.h"

MainCharacter::MainCharacter():
	m_isPlayingEndGame(false)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//------------------------------------------------------------------------
	m_sprite = App::CreateSprite(".\\TestData\\red_ball.bmp");
	m_sprite->SetPosition(50.0f, 100.0f);
	m_debugRenderOn = false;

	m_sprite->SetScale(1.0f);
}

MainCharacter::~MainCharacter()
{
	delete m_sprite;
}

void MainCharacter::Update(float deltaTime)
{
	if (m_isPlayingEndGame)
	{
		return;
	}

	const float SPEED = .15f;

	float deplacement = SPEED * deltaTime;
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		x += deplacement;
		m_sprite->SetPosition(x, y);
	}
	else if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		x -= deplacement;
		m_sprite->SetPosition(x, y);
	}
	else if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		y += deplacement;
		m_sprite->SetPosition(x, y);
	}
	else if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		y -= deplacement;
		m_sprite->SetPosition(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		m_debugRenderOn = !m_debugRenderOn;
	}
	UpdateAABB();
}

void MainCharacter::UpdateAABB()
{
	float x = 0.f;
	float y = 0.f;
	float width = m_sprite->GetWidth();
	float height = m_sprite->GetHeight();
	m_sprite->GetPosition(x, y);

	m_box.x1 = x - width * 0.5f;
	m_box.y1 = y - height * 0.5f;
	m_box.x2 = x + width * 0.5f;
	m_box.y2 = y + height * 0.5f;
}

void MainCharacter::DebugRender()
{
	float x = 0.f;
	float y = 0.f;
	m_sprite->GetPosition(x, y);
	float width = m_sprite->GetWidth();
	float height = m_sprite->GetHeight();


	float xMinPos = x - width * 0.5f;
	float yMinPos = y - height * 0.5f;
	float xMaxPos = x + width * 0.5f;
	float yMaxPos = y + height * 0.5f;


	App::DrawLine(xMinPos, yMinPos, xMaxPos, yMinPos, 1.f, 1.f, 0.f);
	App::DrawLine(xMaxPos, yMinPos, xMaxPos, yMaxPos, 1.f, 1.f, 0.f);
	App::DrawLine(xMaxPos, yMaxPos, xMinPos, yMaxPos, 1.f, 1.f, 0.f);
	App::DrawLine(xMinPos, yMaxPos, xMinPos, yMinPos, 1.f, 1.f, 0.f);
}

void MainCharacter::Render()
{
	m_sprite->Draw();
	if (m_debugRenderOn)
		DebugRender();
}

void MainCharacter::StartEndGame()
{
	m_isPlayingEndGame = true;
}

void MainCharacter::GetCenterPos(float& x, float& y)
{
	m_sprite->GetPosition(x, y);
}
