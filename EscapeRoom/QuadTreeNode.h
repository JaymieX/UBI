#pragma once

#include "GameObject.h"
#include "CollisionComponent.h"

#define QUAD_SIZE 4

namespace EscapeRoom
{
	template <size_t NodeMaxGameObjects, size_t Depth>
	class QuadTreeNode
	{
	private:
		using QuadTreeNodeType = QuadTreeNode<NodeMaxGameObjects, Depth>;

		std::vector<GameObject*> game_objects_ptr;
		size_t current_level;
		Rect node_zone;

		QuadTreeNodeType* children_nodes[QUAD_SIZE];
		
	public:
		QuadTreeNode(const size_t level_, const Rect& node_zone_) :
			current_level(level_),
			node_zone(node_zone_)
		{
			children_nodes[0] = nullptr;
			children_nodes[1] = nullptr;
			children_nodes[2] = nullptr;
			children_nodes[3] = nullptr;
		}

		~QuadTreeNode()
		{
			delete[] children_nodes;
		}

		inline void Draw(QuadTreeNodeType* node_) const
		{
			App::DrawLine(
				node_zone.p1.x,
				node_zone.p1.y,
				node_zone.p4.x,
				node_zone.p4.y,
				0.54f,
				0.06f,
				0.8f
			);

			if (children_nodes[0] != nullptr)
			{
				Draw(children_nodes[0]);
				Draw(children_nodes[1]);
				Draw(children_nodes[2]);
				Draw(children_nodes[3]);
			}
		}

		inline void Draw() const
		{
			Draw(this);
		}

		inline void Clear()
		{
			delete[] children_nodes;
		}

		inline void Divide()
		{
			const MathVector centre = node_zone.GetCentre();
			
			const float new_width = centre.x;
			const float new_height = centre.y;

			const float new_x = centre.x / 2.f;
			const float new_y = centre.y / 2.f;

			// Top left
			children_nodes[0] = new QuadTreeNodeType(
				current_level + 1,
				Rect(
					MathVector(centre.x - new_x, centre.y + new_y),
					new_width,
					new_height
				)
			);

			// Top right
			children_nodes[1] = new QuadTreeNodeType(
				current_level + 1,
				Rect(
					MathVector(centre.x + new_x, centre.y + new_y),
					new_width,
					new_height
				)
			);

			// Bottom right
			children_nodes[2] = new QuadTreeNodeType(
				current_level + 1,
				Rect(
					MathVector(centre.x + new_x, centre.y - new_y),
					new_width,
					new_height
				)
			);

			// Bottom left
			children_nodes[3] = new QuadTreeNodeType(
				current_level + 1,
				Rect(
					MathVector(centre.x - new_x, centre.y - new_y),
					new_width,
					new_height
				)
			);
		}

		inline int Fit(const Rect& node_zone_) const
		{
			int node_index = -1; // Not fit, part of parent
			
			const MathVector this_centre = node_zone.GetCentre();
			const MathVector other_centre = node_zone_.GetCentre();

			const bool left = node_zone_.p2.x < this_centre.x && node_zone_.p1.x > node_zone.p1.x;
			const bool right = node_zone_.p1.x > this_centre.x && node_zone_.p2.x < node_zone.p2.x;

			// Top
			if (node_zone_.p4.y > this_centre.y && node_zone_.p1.y < node_zone.p1.y)
			{
				// Top left
				if (left)
				{
					node_index = 0;
				}
				// Top right
				else if (right)
				{
					node_index = 1;
				}
			}
			// Bottom
			else if (node_zone_.p1.y < this_centre.y && node_zone_.p4.y > node_zone.p4.y)
			{
				// Bottom left
				if (left)
				{
					node_index = 3;
				}
				// Bottom right
				else if (right)
				{
					node_index = 2;
				}
			}

			return node_index;
		}

		inline void Insert(GameObject* object_)
		{
			const Rect zone = object_->GetComponent<AABBCollisionComponent>()->GetActualCollisionZone();
			
			if (children_nodes[0] != nullptr)
			{
				const int index = Fit(zone);

				// Make sure it fits
				if (index != -1)
				{
					children_nodes[index]->Insert(object_);
					return;
				}
			}

			// Add game object
			game_objects_ptr.emplace_back(object_);

			// Dont exceed max level
			if (current_level > Depth) return;

			if (game_objects_ptr.size() > NodeMaxGameObjects)
			{
				// Dividing
				if (children_nodes[0] == nullptr)
				{
					Divide();
				}

				int i = 0;
				while (i < game_objects_ptr.size())
				{
					int index = Fit(game_objects_ptr.at(i)->GetComponent<AABBCollisionComponent>()->GetActualCollisionZone());
					if (index != -1) {
						children_nodes[index]->Insert(game_objects_ptr.erase(game_objects_ptr.begin() + i));
					}
					else
					{
						i++;
					}
				}
			}
		}

		inline std::vector<GameObject*> GetObjects(std::vector<GameObject*>& obj_list_, GameObject* target_)
		{
			const Rect zone = target_->GetComponent<AABBCollisionComponent>()->GetActualCollisionZone();
			const int index = Fit(zone);

			if (index != -1 && children_nodes[0] != nullptr)
			{
				children_nodes[index]->GetObjects(obj_list_, target_);
			}

			for (auto obj : game_objects_ptr)
			{
				obj_list_.emplace_back(obj);
			}

			return obj_list_;
		}

		inline std::vector<GameObject*> GetObjects(GameObject* target_)
		{
			std::vector<GameObject*> result;
			GetObjects(result, target_);

			return result;
		}
		
	};
}
