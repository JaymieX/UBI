#include "stdafx.h"
#include "SceneLevel0.h"

#include "ShapeComponent.h"
#include "SpriteComponent.h"
#include "PlayerControlComponent.h"
#include "CollisionComponent.h"
#include "ShapeAnimatorComponent.h"
#include "PathControlComponent.h"

void EscapeRoom::SceneLevel0::PlayerCollidedEnter(GameObject* other_)
{
	if (other_->GetComponent<ICollisionComponent>()->GetTrigger())
	{
		if (other_->tag == "killer")
		{
			player_object->SetPosition(player_start);
			player_object->GetComponent<PlayerControlComponent>()->velocity = 0.f;
		}
	}
}

void EscapeRoom::SceneLevel0::PlayerCollidedExit(GameObject* other_)
{
}

void EscapeRoom::SceneLevel0::MakeWallObject(MathVector&& position_, const float width_, const float height_)
{
	Rect box(MathVector(0.f, 0.f), 1.f, 1.f);

	std::string name = "wall-object_";
	name.append(std::to_string(wall_objects.size()));
	
	GameObject* wall = AddGameObject(std::move(name));
	wall->SetPosition(position_);
	wall->SetScale(MathVector(width_, height_));

	AddComponentToGameObject<ShapeComponent>(
		wall,
		LinePackFactory::MakeRect(box),
		MathVector(.6f, .6f, .6f)
		);
	AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(wall, box);

	wall_objects.emplace_back(wall);
}

EscapeRoom::GameObject* EscapeRoom::SceneLevel0::MakeKillerObjectB(MathVector&& position_)
{
	Rect box(MathVector(0.f, 0.f), 1.f, 1.f);
	
	GameObject* killer_object1 = AddGameObject(GetNextGameObjectID());
	killer_object1->SetPosition(position_);
	killer_object1->SetScale(MathVector(60.f, 60.f));
	killer_object1->tag = "killer";

	AABBCollisionComponent* killer_col_1 = AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(killer_object1, box);
	killer_col_1->SetTrigger(true);

	GameObject* killer_object1_1 = AddGameObject(GetNextGameObjectID());
	AddComponentToGameObject<ShapeComponent>(
		killer_object1_1,
		LinePackFactory::MakeStar4C(),
		MathVector(.6f, .6f, .6f)
		);

	AddComponentToGameObject<ShapeAnimatorComponent>(
		killer_object1_1, 0.08f
		);

	killer_object1->AddChildGameObject(killer_object1_1);

	GameObject* killer_object1_1_1 = AddGameObject(GetNextGameObjectID());
	killer_object1_1_1->SetScale(MathVector(.5f, .5f));
	killer_object1_1_1->SetPosition(MathVector(-50.f, 0.f));

	AddComponentToGameObject<ShapeComponent>(
		killer_object1_1_1,
		LinePackFactory::MakeStar4C(),
		MathVector(.6f, .6f, .6f)
		);

	AddComponentToGameObject<ShapeAnimatorComponent>(
		killer_object1_1_1, 0.08f
		);

	killer_object1_1->AddChildGameObject(killer_object1_1_1);

	return killer_object1;
}

EscapeRoom::GameObject* EscapeRoom::SceneLevel0::MakekillerObjectA(MathVector&& position_)
{
	Rect box(MathVector(0.f, 0.f), 1.f, 1.f);
	
	GameObject* killer_object0 = AddGameObject(GetNextGameObjectID());
	killer_object0->SetPosition(position_);
	killer_object0->SetScale(MathVector(100.f, 100.f));
	killer_object0->tag = "killer";

	AddComponentToGameObject<ShapeComponent>(
		killer_object0,
		LinePackFactory::MakeStar4C(),
		MathVector(.6f, .6f, .6f)
		);

	AABBCollisionComponent* killer_col_0 = AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(killer_object0, box);
	killer_col_0->SetTrigger(true);

	return killer_object0;
}

void EscapeRoom::SceneLevel0::StartScene()
{
	IScene::StartScene();

	Rect box(MathVector(0.f, 0.f), 1.f, 1.f);

	Rect player_collision_box(MathVector(0.f, 0.f), 60.f, 60.f);

	// Player
	player_object = AddGameObject("player-object");
	player_object->affected_by_collision = true;
	player_start = MathVector(100.f, 100.f);
	player_object->SetPosition(player_start);
	
	AddComponentToGameObject<SpriteComponent>(
		player_object,
		".\\TestData\\red_ball.bmp"
		);
	player_controller = AddComponentToGameObject<PlayerControlComponent>(player_object, 0.16f);
	AABBCollisionComponent* player_col = AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(
		player_object,
		player_collision_box);
	
	player_col->on_collision_call_backs.Connect(
		this,
		&SceneLevel0::PlayerCollidedEnter
	);

	player_col->on_collision_exit_call_backs.Connect(
		this,
		&SceneLevel0::PlayerCollidedExit
	);

#define THICKNESS 10.f

	// Walls
	MakeWallObject(MathVector(50.f, 390.f), THICKNESS, 700.f);
	MakeWallObject(MathVector(960.f, 390.f), THICKNESS, 700.f);
	MakeWallObject(MathVector(505.f, 740.f), 910.f, THICKNESS);
	MakeWallObject(MathVector(505.f, 40.f), 910.f, THICKNESS);
	
	MakeWallObject(MathVector(205.f, 275.f), THICKNESS, 400.f);
	MakeWallObject(MathVector(160.f, 175.f), 80.f, THICKNESS);
	MakeWallObject(MathVector(80.f, 325.f), 80.f, THICKNESS);
	MakeWallObject(MathVector(160.f, 445.f), 80.f, THICKNESS);
	MakeWallObject(MathVector(501.f, 500.f), 600.f, THICKNESS);
	MakeWallObject(MathVector(600.f, 550.f), THICKNESS, 100.f);

	MakeWallObject(MathVector(630.f, 400.f), 650.f, THICKNESS);
	MakeWallObject(MathVector(300.f, 300.f), THICKNESS, 260.f);
	MakeWallObject(MathVector(425.f, 170.f), 250.f, THICKNESS);
	MakeWallObject(MathVector(825.f, 170.f), 250.f, THICKNESS);
	MakeWallObject(MathVector(700.f, 270.f), THICKNESS, 200.f);
	
	// Moving platforms
	// p1
	GameObject* platform_object0 = AddGameObject("platform-object0");
	platform_object0->SetPosition(MathVector(-100.f, 670.f));
	platform_object0->SetScale(MathVector(1000.f, 150.f));

	AddComponentToGameObject<ShapeComponent>(
		platform_object0,
		LinePackFactory::MakeRect(box),
		MathVector(.6f, .6f, .6f)
	);
	Points points;
	points.emplace_back(MathVector(200.f, 670.f));
	points.emplace_back(MathVector(-100.f, 670.f));
	AddComponentToGameObject<PathControlComponent>(platform_object0, std::move(points), 0.05f);
	
	AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(platform_object0, box);

	// p2
	GameObject* platform_object1 = AddGameObject("platform-object1");
	platform_object1->SetPosition(MathVector(700.f, -100.f));
	platform_object1->SetScale( MathVector(100.f, 150.f));

	AddComponentToGameObject<ShapeComponent>(
		platform_object1,
		LinePackFactory::MakeRect(box),
		MathVector(.6f, .6f, .6f)
		);
	Points points2;
	points2.emplace_back(MathVector(700.f, 120.f));
	points2.emplace_back(MathVector(700.f, -100.f));
	AddComponentToGameObject<PathControlComponent>(platform_object1, std::move(points2), 0.05f);

	AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(platform_object1, box);

	// Killer
	// k1
	MakekillerObjectA(MathVector(600.f, 760.f));
	MakekillerObjectA(MathVector(660.f, 550.f));

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
}

void EscapeRoom::SceneLevel0::UpdateScene()
{
	debug_collided = false;
	
	IScene::UpdateScene();
}

void EscapeRoom::SceneLevel0::RenderScene()
{
	IScene::RenderScene();

	if (debug_collided)
	{
		App::Print(500, 400, "!!! PlayerCollided !!!");
	}
}

void EscapeRoom::SceneLevel0::EndScene()
{
	IScene::RenderScene();
}
