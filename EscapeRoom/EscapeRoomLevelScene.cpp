#include "stdafx.h"
#include "EscapeRoomLevelScene.h"

void EscapeRoom::EscapeRoomLevelScene::PlayerCollidedEnter(GameObject* other_)
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

void EscapeRoom::EscapeRoomLevelScene::MakeWallObject(MathVector&& position_, const float width_, const float height_)
{
	// Object
	GameObject* wall = AddGameObject(GetNextGameObjectID());
	wall->SetPosition(position_);
	wall->SetScale(MathVector(width_, height_));

	// Components
	AddComponentToGameObject<ShapeComponent>(
		wall,
		LinePackFactory::MakeRect(base_box),
		MathVector(.6f, .6f, .6f)
		);
	AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(wall, base_box);
}

EscapeRoom::GameObject* EscapeRoom::EscapeRoomLevelScene::MakeKillerObjectB(MathVector&& position_)
{
	GameObject* killer_object1 = AddGameObject(GetNextGameObjectID());
	killer_object1->SetPosition(position_);
	killer_object1->SetScale(MathVector(60.f, 60.f));
	killer_object1->tag = "killer";

	AABBCollisionComponent* killer_col_1 =
		AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(killer_object1, base_box);
	killer_col_1->SetTrigger(true);

	GameObject* killer_object1_1 = AddGameObject(GetNextGameObjectID());
	AddComponentToGameObject<ShapeComponent>(
		killer_object1_1,
		LinePackFactory::MakeStar4C(),
		MathVector(.6f, .6f, .6f)
		);

	AddComponentToGameObject<ShapeAnimatorComponent>(
		killer_object1_1, 0.005f
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
		killer_object1_1_1, 0.005f
		);

	killer_object1_1->AddChildGameObject(killer_object1_1_1);

	return killer_object1;
}

EscapeRoom::GameObject* EscapeRoom::EscapeRoomLevelScene::MakeKillerObjectA(MathVector&& position_)
{
	GameObject* killer_object0 = AddGameObject(GetNextGameObjectID());
	killer_object0->SetPosition(position_);
	killer_object0->SetScale(MathVector(100.f, 100.f));
	killer_object0->tag = "killer";

	AddComponentToGameObject<ShapeComponent>(
		killer_object0,
		LinePackFactory::MakeStar4C(),
		MathVector(.6f, .6f, .6f)
		);

	AABBCollisionComponent* killer_col_0 =
		AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(killer_object0, base_box);
	killer_col_0->SetTrigger(true);

	return killer_object0;
}

void EscapeRoom::EscapeRoomLevelScene::MakePlatformObject(MathVector&& start_, MathVector&& end_, MathVector&& scale_)
{
	GameObject* platform_object0 = AddGameObject(GetNextGameObjectID());
	platform_object0->SetPosition(start_);
	platform_object0->SetScale(scale_);

	AddComponentToGameObject<ShapeComponent>(
		platform_object0,
		LinePackFactory::MakeRect(base_box),
		MathVector(.6f, .6f, .6f)
		);

	Points points;
	points.emplace_back(end_);
	points.emplace_back(start_);
	AddComponentToGameObject<PathControlComponent>(platform_object0, std::move(points), 0.05f);

	AddComponentToGameObjectEx<AABBCollisionComponent, ICollisionComponent>(platform_object0, base_box);
}

void EscapeRoom::EscapeRoomLevelScene::MakePlayer(const MathVector& position_)
{
	Rect player_collision_box(MathVector(0.f, 0.f), 60.f, 60.f);

	// Player
	player_object = AddGameObject("player-object");
	player_object->affected_by_collision = true;

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
		&EscapeRoomLevelScene::PlayerCollidedEnter
	);
}
