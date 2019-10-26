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
	debug_collided = true;
	player_controller->SetVelocity(MathVector());
	player_controller->freeze_movement = true;

	//player_controller->GetOwner()->velocity = 0.f;
	//player_controller->GetOwner()->position -= player_controller->GetLastVelocity();
}

void EscapeRoom::SceneLevel0::PlayerCollidedExit(GameObject* other_)
{
	player_controller->freeze_movement = false;
}

void EscapeRoom::SceneLevel0::MakeWallObject(MathVector&& position_, const float width_, const float height_)
{
	Rect box(MathVector(0.f, 0.f), 1.f, 1.f);
	
	GameObject* wall = AddGameObject("wall-object_" + wall_objects.size());
	wall->position = position_;
	wall->scale = MathVector(width_, height_);

	AddComponentToGameObject<ShapeComponent>(
		wall,
		LinePackFactory::MakeRect(box),
		MathVector(.6f, .6f, .6f)
		);
	AddComponentToGameObject<AABBCollisionComponent>(wall, box);

	wall_objects.emplace_back(wall);
}

void EscapeRoom::SceneLevel0::StartScene()
{
	IScene::StartScene();

	Rect box(MathVector(0.f, 0.f), 1.f, 1.f);

	Rect player_collision_box(MathVector(0.f, 0.f), 60.f, 60.f);

	// Player
	player_object = AddGameObject("player-object");
	player_object->affected_by_collision = true;
	player_object->position = MathVector(100.f, 100.f);
	
	AddComponentToGameObject<SpriteComponent>(
		player_object,
		".\\TestData\\red_ball.bmp"
		);
	player_controller = AddComponentToGameObject<PlayerControlComponent>(player_object, 0.2f);
	AABBCollisionComponent* player_col = AddComponentToGameObject<AABBCollisionComponent>(
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

	// Walls
	MakeWallObject(MathVector(50.f, 390.f), 0.f, 700.f);
	MakeWallObject(MathVector(960.f, 390.f), 0.f, 700.f);
	MakeWallObject(MathVector(505.f, 740.f), 910.f, 0.f);
	MakeWallObject(MathVector(505.f, 40.f), 910.f, 0.f);
	
	MakeWallObject(MathVector(200.f, 275.f), 0.f, 500.f);
	MakeWallObject(MathVector(160.f, 175.f), 80.f, 0.f);
	MakeWallObject(MathVector(80.f, 325.f), 80.f, 0.f);
	MakeWallObject(MathVector(160.f, 475.f), 80.f, 0.f);

	// Moving platforms
	GameObject* platform_object0 = AddGameObject("platform-object0");
	platform_object0->position = MathVector(240.f, 650.f);
	platform_object0->scale = MathVector(0.f, 100.f);

	AddComponentToGameObject<ShapeComponent>(
		platform_object0,
		LinePackFactory::MakeRect(box),
		MathVector(.6f, .6f, .6f)
	);
	Points points;
	points.emplace_back(MathVector(700.f, 650.f));
	points.emplace_back(MathVector(240.f, 650.f));
	AddComponentToGameObject<PathControlComponent>(platform_object0, std::move(points), 0.1f);
	
	AddComponentToGameObject<AABBCollisionComponent>(platform_object0, box);
	
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
