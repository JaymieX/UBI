#include "stdafx.h"
#include "SceneLevel0.h"

#include "PathControlComponent.h"
#include "EscapeRoomLevelScene.h"

void EscapeRoom::SceneLevel0::StartScene()
{
	player_start = MathVector(100.f, 100.f);
	IScene::StartScene();
	
	MakePlayer(player_start);

	// Walls
	MakeWallObject(MathVector(50.f, 390.f), WALL_THICKNESS, 700.f);
	MakeWallObject(MathVector(960.f, 390.f), WALL_THICKNESS, 700.f);
	MakeWallObject(MathVector(505.f, 740.f), 910.f, WALL_THICKNESS);
	MakeWallObject(MathVector(505.f, 40.f), 910.f, WALL_THICKNESS);
	
	MakeWallObject(MathVector(205.f, 275.f), WALL_THICKNESS, 400.f);
	MakeWallObject(MathVector(160.f, 175.f), 80.f, WALL_THICKNESS);
	MakeWallObject(MathVector(80.f, 300.f), 80.f, WALL_THICKNESS);
	MakeWallObject(MathVector(175.f, 465.f), 85.f, WALL_THICKNESS);
	MakeWallObject(MathVector(501.f, 500.f), 600.f, WALL_THICKNESS);
	MakeWallObject(MathVector(600.f, 550.f), WALL_THICKNESS, 100.f);

	MakeWallObject(MathVector(630.f, 400.f), 650.f, WALL_THICKNESS);
	MakeWallObject(MathVector(300.f, 300.f), WALL_THICKNESS, 260.f);
	MakeWallObject(MathVector(425.f, 170.f), 250.f, WALL_THICKNESS);
	MakeWallObject(MathVector(825.f, 170.f), 250.f, WALL_THICKNESS);
	MakeWallObject(MathVector(700.f, 270.f), WALL_THICKNESS, 200.f);
	
	// Moving platforms
	// p1
	MakePlatformObject(
		MathVector(-100.f, 670.f),
		MathVector(200.f, 670.f),
		MathVector(1000.f, 150.f)
	);

	// p2
	MakePlatformObject(
		MathVector(700.f, -100.f),
		MathVector(700.f, 120.f),
		MathVector(100.f, 150.f)
	);

	// Killer
	// k1
	MakeKillerObjectA(MathVector(600.f, 760.f));
	MakeKillerObjectA(MathVector(660.f, 550.f));

	//k2
	GameObject* killer_object2 = MakeKillerObjectB(MathVector(800.f, 450.f));

	Points points3;
	points3.emplace_back(MathVector(800.f, 450.f));
	points3.emplace_back(MathVector(250.f, 450.f));
	points3.emplace_back(MathVector(250.f, 120.f));
	points3.emplace_back(MathVector(800.f, 120.f));
	points3.emplace_back(MathVector(800.f, 450.f));
	points3.emplace_back(MathVector(250.f, 450.f));
	points3.emplace_back(MathVector(250.f, 120.f));
	points3.emplace_back(MathVector(800.f, 120.f));
	AddComponentToGameObject<PathControlComponent>(killer_object2, std::move(points3), 0.1f);

	// K3
	MakeKillerObjectB(MathVector(480.f, 340.f));

	// K4
	MakeKillerObjectA(MathVector(890.f, 100.f));

	// Exit
	MakeExitObject(MathVector(380.f, 240.f));
}