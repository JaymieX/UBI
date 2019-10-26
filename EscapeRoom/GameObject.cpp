#include "stdafx.h"
#include "GameObject.h"

#include "IComponent.h"

EscapeRoom::GameObject::GameObject(const std::string& name_, IScene* scene_) :
	name(name_),
	owner_scene(scene_),
	position(0.f, 0.f, 0.f),
	rotation(0.f, 0.f, 0.f),
	scale(1.f, 1.f, 1.f)
{
}

void EscapeRoom::GameObject::AddChildGameObject(GameObject* game_object_)
{
	game_object_->parent = this;
	children.emplace(game_object_);
}

void EscapeRoom::GameObject::ServiceAllComponents(std::function<void(IComponent*)>&& service_func_)
{
	for (auto& vec : components)
	{
		for (auto& comp : vec.second)
		{
			service_func_(comp);
		}
	}
}

void EscapeRoom::GameObject::StartGameObject()
{
	ServiceAllComponents([](IComponent* comp_) { comp_->StartComponent(); });
}

void EscapeRoom::GameObject::UpdateGameObject()
{
	position += velocity;
	
	translate_mat	= MathMatrix::Translate(position);
	rotation_mat	= MathMatrix::Rotate(rotation, angle);
	scale_mat		= MathMatrix::Scale(scale);

	if (parent != nullptr)
	{
		//Parent_Pos * Parent_Rotation* My_Pos* My_Rotation* Parent_Scale* My_Scale
		transform =
			parent->translate_mat *
			parent->rotation_mat *
			translate_mat *
			rotation_mat *
			parent->scale_mat *
			scale_mat;
	}
	else
	{
		transform =
			translate_mat *
			rotation_mat *
			scale_mat;
	}
	
	ServiceAllComponents([](IComponent* comp_) { comp_->UpdateComponent(); });
}

void EscapeRoom::GameObject::RenderGameObject()
{
	ServiceAllComponents([](IComponent* comp_) { comp_->RenderComponent(); });
}

void EscapeRoom::GameObject::DrawLine(MathMatrix4x4& mat_, Line& line_, float r_, float g_, float b_)
{
	const MathVector transformed_start = mat_ * line_.start;
	const MathVector transformed_end = mat_ * line_.end;

	App::DrawLine(
		transformed_start.x,
		transformed_start.y,
		transformed_end.x,
		transformed_end.y,
		r_, g_, b_
	);
}