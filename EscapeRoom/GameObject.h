#pragma once

#include "GUID.h"

namespace EscapeRoom
{
	class IScene;
	class IComponent;

	struct Rect
	{
		MathVector p1;
		MathVector p2;
		MathVector p3;
		MathVector p4;

		Rect(MathVector& p1_, MathVector& p2_, MathVector& p3_, MathVector& p4_) :
			p1(p1_),
			p2(p2_),
			p3(p3_),
			p4(p4_)
		{
		}

		Rect(MathVector&& centre_, const float width_, const float height_) :
			p1(centre_.x - width_ * .5f, centre_.y + height_ * .5f),
			p2(centre_.x + width_ * .5f, centre_.y + height_ * .5f),
			p3(centre_.x + width_ * .5f, centre_.y - height_ * .5f),
			p4(centre_.x - width_ * .5f, centre_.y - height_ * .5f)
		{
		}

		inline float GetWidth() const
		{
			return abs(p2.x - p1.x);
		}

		inline float GetHeight() const
		{
			return abs(p4.y - p1.y);
		}

		inline MathVector GetCentre() const
		{
			MathVector result;
			result.x = p1.x + GetWidth() / 2.f;
			result.y = p4.y + GetHeight() / 2.f;

			return result;
		}
	};

	struct Line
	{
		MathVector start, end;

		Line(const MathVector& start_, const MathVector& end_) :
			start(start_),
			end(end_)
		{
		}
	};

	using LinePack = std::vector<Line>;

	class LinePackFactory
	{
	public:
		inline static LinePack MakeRect(Rect& rect_)
		{
			LinePack result;

			result.emplace_back(Line{ rect_.p1, rect_.p2 });
			result.emplace_back(Line{ rect_.p2, rect_.p3 });
			result.emplace_back(Line{ rect_.p3, rect_.p4 });
			result.emplace_back(Line{ rect_.p4, rect_.p1 });

			return result;
		}

		inline static LinePack MakeStar4C()
		{
			LinePack result;

			result.emplace_back(Line(MathVector(-0.5,0), MathVector(-0.18, -0.18)));
			result.emplace_back(Line(MathVector(-0.18, -0.18), MathVector(0, -0.5)));
			result.emplace_back(Line(MathVector(0, -0.5), MathVector(0.18, -0.18)));
			result.emplace_back(Line(MathVector(0.18, -0.18), MathVector(0.5, 0)));
			result.emplace_back(Line(MathVector(0.5, 0), MathVector(0.18, 0.18)));
			result.emplace_back(Line(MathVector(0.18, 0.18), MathVector(0, 0.5)));
			result.emplace_back(Line(MathVector(0, 0.5), MathVector(-0.18, 0.18)));
			result.emplace_back(Line(MathVector(-0.18, 0.18), MathVector(-0.5, 0)));

			return result;
		}
	};
	
	class GameObject
	{
	private:
		friend class IScene;
		
		std::string name;

		GameObject* parent = nullptr;
		std::set<GameObject*> children;
		
		std::unordered_map<GameTypeGUID::GUIDType, std::vector<IComponent*>> components;

		IScene* owner_scene;

		void ServiceAllComponents(std::function<void(IComponent*)>&& service_func_);
		
	public:
		MathVector position;
		MathVector rotation;
		MathVector scale;
		float angle;

		MathMatrix4x4 translate_mat;
		MathMatrix4x4 rotation_mat;
		MathMatrix4x4 scale_mat;
		
		MathMatrix4x4 transform;

		MathVector velocity;
		
		bool affected_by_collision = false;

		std::string tag {"default" };

		explicit GameObject(const std::string& name_, IScene* scene_);
		
		void AddChildGameObject(GameObject* game_object_);

		template <typename Comp>
		Comp* GetComponent();
		
		void StartGameObject();

		void UpdateGameObject();

		void RenderGameObject();

		MathMatrix4x4 GetParentHierarchicalTRMatrix();
		MathMatrix4x4 GetParentHierarchicalSMatrix();

		static void DrawLine(MathMatrix4x4& mat_, Line& line_, float r_, float g_, float b_);
	};
}

#include "IComponent.h"
template <typename Comp>
Comp* EscapeRoom::GameObject::GetComponent()
{
	if (Util::MapContains(components, GameTypeGUID::GetGUID<Comp>()))
	{
		return
		dynamic_cast<Comp*>(components.at(GameTypeGUID::GetGUID<Comp>()).at(0));
	}

	return nullptr;
}