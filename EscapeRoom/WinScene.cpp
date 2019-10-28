#include "stdafx.h"
#include "WinScene.h"

void EscapeRoom::WinScene::UpdateScene()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP))
	{
		SceneSystem::GetInstance()->SwitchToScene("scene-0");
	}
}

void EscapeRoom::WinScene::RenderScene()
{
	App::Print(480, 600, "You won~~~~");
	App::Print(480, 500, "Press up to play again");
	App::Print(480, 400, "Press ESC to quit");
}
