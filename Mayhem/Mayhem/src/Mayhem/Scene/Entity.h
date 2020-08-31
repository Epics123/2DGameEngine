#pragma once

#include "Scene.h"

#include "entt.hpp"

namespace Mayhem
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			MH_CORE_ASSERT(!hasComponent<T>(), "Entity already has component!");
			return mScene->mRegistry.emplace<T>(mEntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent()
		{
			MH_CORE_ASSERT(hasComponent<T>(), "Entity does not have component!");
			return mScene->mRegistry.get<T>(mEntityHandle);
		}

		template<typename T>
		bool hasComponent()
		{
			return mScene->mRegistry.has<T>(mEntityHandle);
		}

		template<typename T>
		bool removeComponent()
		{
			MH_CORE_ASSERT(hasComponent<T>(), "Entity does not have component!");
			return mScene->mRegistry.remove<T>(mEntityHandle);
		}

		operator bool() const { return mEntityHandle != entt::null; }

	private:
		entt::entity mEntityHandle{ entt::null };
		Scene* mScene = nullptr;
	};
}