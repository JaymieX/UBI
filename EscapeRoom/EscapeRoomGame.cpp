#include "stdafx.h"

#include <windows.h> 
#include <cmath>  
//------------------------------------------------------------------------

#include "SceneSystem.h"
#include "SceneLevel0.h"

enum GameState
{
	RUNNING,
	WIN,
	LOST
};

GameState GlobalState = RUNNING;

EscapeRoom::SceneSystem* scene_system;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	scene_system = new EscapeRoom::SceneSystem();
	scene_system->AddScene<EscapeRoom::SceneLevel0>("scene-0");
	scene_system->SwitchToScene("scene-0");
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
	if (GlobalState == RUNNING)
	{
		scene_system->UpdateScene(deltaTime);
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	scene_system->RenderScene();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	delete scene_system;
}