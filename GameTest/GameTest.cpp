//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app.h"
#include "MainCharacter.h"
#include "Door.h"

#include "AABB.h"

#include "LaserWall.h"

#include <vector>
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
//------------------------------------------------------------------------
MainCharacter* m_mainCharacter = nullptr;
Door* m_door = nullptr;
bool m_isFinish = false;
std::vector<LaserWall> wallList;

enum GameState
{
	RUNNING,
	WIN,
	LOST
} ;

GameState globalState = RUNNING;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	m_mainCharacter = new MainCharacter();
	m_door = new Door(900, 600, 100, 200);
	LaserWall wall1 = LaserWall(10, 1000, 10, 10);
	LaserWall wall2 = LaserWall(10, 1000, 750, 750);
	LaserWall wall3 = LaserWall(10, 10, 10, 750);
	LaserWall wall4 = LaserWall(1000, 1000, 10, 750);
	LaserWall wall5 = LaserWall(300, 300, 10, 500);
	LaserWall wall6 = LaserWall(600, 600, 750, 200);
	wallList.push_back(wall1);
	wallList.push_back(wall2);
	wallList.push_back(wall3);
	wallList.push_back(wall4);
	wallList.push_back(wall5);
	wallList.push_back(wall6);

}

void StartEndGame()
{
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::StartSound(".\\TestData\\Test.wav");
	}

	m_mainCharacter->StartEndGame();
	m_door->StartEndGame();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	m_mainCharacter->Update(deltaTime);
	m_door->Update(deltaTime);

	if (globalState == RUNNING)
	{
		float xMainCharPos = 0.f;
		float yMainCharPos = 0.f;

		if (areColliding(m_mainCharacter->GetAABB(), m_door->GetAABB()))
		{
			StartEndGame();
			globalState = WIN;
		}
		for (auto wall : wallList)
		{
			if (areColliding(m_mainCharacter->GetAABB(), wall.GetAABB()))
			{
				StartEndGame();
				globalState = LOST;
			}
		}
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	// The order is important to have the main character above the door
	m_door->Render();

	m_mainCharacter->Render();

	for (auto wall : wallList)
	{
		wall.Render();
	}

	if (globalState == WIN)
	{
		//------------------------------------------------------------------------
		// Example Text.
		App::Print(500, 400, "!!! WIN !!!");
		//------------------------------------------------------------------------
	}
	if (globalState == LOST)
	{
		//------------------------------------------------------------------------
		// Example Text.
		App::Print(500, 400, "!!! LOST !!!");
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	delete m_mainCharacter;
	delete m_door;
}
