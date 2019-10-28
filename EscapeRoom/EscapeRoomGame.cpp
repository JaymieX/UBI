#include "stdafx.h"

#include <windows.h> 
#include <cmath>  
//------------------------------------------------------------------------

#include "SceneSystem.h"
#include "SceneLevel0.h"
#include "WinScene.h"

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	EscapeRoom::SceneSystem::GetInstance()->AddScene<EscapeRoom::SceneLevel0>("scene-0");
	EscapeRoom::SceneSystem::GetInstance()->AddScene<EscapeRoom::WinScene>("scene-win");
	EscapeRoom::SceneSystem::GetInstance()->SwitchToScene("scene-0");
}

void StartEndGame()
{
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (EscapeRoom::SceneSystem::GetInstance()->global_state == EscapeRoom::SceneSystem::RUNNING)
	{
		EscapeRoom::SceneSystem::GetInstance()->UpdateScene(deltaTime);
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	EscapeRoom::SceneSystem::GetInstance()->RenderScene();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
}