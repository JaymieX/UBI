#pragma once

#include "GameObject.h"
#include "IComponent.h"
#include "GUID.h"
#include "QuadTreeNode.h"

namespace EscapeRoom
{
	class IScene
	{
	private:
		friend class GameObject;
		
		std::unordered_map<std::string, std::unique_ptr<GameObject>> game_objects;
		std::unordered_map<GameTypeGUID::GUIDType, std::vector<std::unique_ptr<IComponent>>> components;

		Rect screen;

		QuadTreeNode<2, 3> quad_tree;
		
	protected:
		GameObject* AddGameObject(std::string&& name_);

		GameObject* GetGameObject(std::string&& name_);
		
		template <typename Comp, typename ... Args>
		Comp* AddComponentToGameObject(GameObject* owner_, Args&&... args_)
		{
			// Static assert
			static_assert(
				std::is_convertible<Comp*, IComponent*>::value,
				"Comp must publicly inherit from IComponent"
				);

			// Make sure pool exists
			if (!Util::MapContains(components, GameTypeGUID::GetGUID<Comp>()))
			{
				components.insert(
					std::make_pair(
						GameTypeGUID::GetGUID<Comp>(),
						std::vector < std::unique_ptr<IComponent>>()
					)
				);
			}

			if (!Util::MapContains(owner_->components, GameTypeGUID::GetGUID<Comp>()))
			{
				owner_->components.insert(
					std::make_pair(
						GameTypeGUID::GetGUID<Comp>(),
						std::vector<IComponent*>()
					)
				);
			}

			// Add
			std::unique_ptr<Comp> u_ptr = std::make_unique<Comp>(owner_, std::forward<Args>(args_)...);
			Comp* ptr = dynamic_cast<Comp*>(u_ptr.get());
			components.at(GameTypeGUID::GetGUID<Comp>()).emplace_back(
				std::move(u_ptr)
			);

			owner_->components.at(GameTypeGUID::GetGUID<Comp>()).emplace_back(ptr);

			// Get
			return ptr;
		}
		
	public:
		IScene() :
			screen(MathVector(500.f, 380.f), 1000.f, 800.f),
			quad_tree(0, screen)
		{
		}

		virtual ~IScene()
		{
			components.clear();
			game_objects.clear();
		}
		
		virtual void StartScene() {}

		void StartGameObjects()
		{
			for (auto& object : game_objects)
			{
				object.second->StartGameObject();
			}
		}

		virtual void UpdateScene();

		virtual void RenderScene()
		{
			for (auto& object : game_objects)
			{
				object.second->RenderGameObject();
			}

			quad_tree.Draw();
		}

		virtual void EndScene() {}

		inline std::string GetNextGameObjectID() const
		{
			std::string result = "game-object-";
			result.append(std::to_string(game_objects.size()));
			return result;
		}
	};
	
	class SceneSystem final
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<IScene>> available_scenes;

		IScene* current_scene = nullptr;

		static float delta_time;

		SceneSystem() = default;
		
	public:
		~SceneSystem()
		{
			available_scenes.clear();
		}

		inline static SceneSystem* GetInstance()
		{
			static SceneSystem instance;
			return &instance;
		}
		
		inline static float GetDeltaTime()
		{
			return delta_time;
		}
		
		template <typename SceneType, typename ...Args>
		inline bool AddScene(std::string&& name_, Args&&... args_)
		{
			// Static assert
			static_assert(
				std::is_convertible<SceneType*, IScene*>::value,
				"SceneType must publicly inherit from IScene"
			);

			// Make sure we do not have scene with same name
			if (!Util::MapContains(available_scenes, name_))
			{
				available_scenes.insert(
					std::make_pair(
						name_,
						std::make_unique<SceneType>(std::forward<Args>(args_)...)
					)
				);

				return true;
			}

			return false;
		}

		inline bool SwitchToScene(std::string&& name_)
		{
			// Make sure we have said scene
			if (Util::MapContains(available_scenes, name_))
			{
				// If one scene is currently running
				if (current_scene != nullptr)
				{
					current_scene->EndScene();
				}

				// Switching
				current_scene = available_scenes.at(name_).get();
				current_scene->StartScene();
				current_scene->StartGameObjects();

				return true;
			}

			return false;
		}

		inline void UpdateScene(float delta_time_) const
		{
			delta_time = delta_time_;
			
			if (current_scene != nullptr)
			{
				current_scene->UpdateScene();
			}
		}

		inline void RenderScene() const
		{
			if (current_scene != nullptr)
			{
				current_scene->RenderScene();
			}
		}
	};
	
}
