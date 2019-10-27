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
	AppendPosition(velocity);

	// Parent_Rotation Parent_Pos * My_Pos * My_Rotation * Parent_Scale * My_Scale
	transform = GetParentHierarchicalTRMatrix() * GetParentHierarchicalSMatrix();
	
	ServiceAllComponents([](IComponent* comp_) { comp_->UpdateComponent(); });
}

void EscapeRoom::GameObject::RenderGameObject()
{
	ServiceAllComponents([](IComponent* comp_) { comp_->RenderComponent(); });
}

EscapeRoom::MathMatrix4x4 EscapeRoom::GameObject::GetParentHierarchicalTRMatrix()
{
	if (parent != nullptr)
	{
		return parent->GetParentHierarchicalTRMatrix() * rotation_mat * translate_mat;
	}

	return translate_mat * rotation_mat;
}

EscapeRoom::MathMatrix4x4 EscapeRoom::GameObject::GetParentHierarchicalSMatrix()
{
	if (parent != nullptr)
	{
		return parent->GetParentHierarchicalSMatrix() * scale_mat;
	}

	return scale_mat;
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
