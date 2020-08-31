#pragma once

#include "entt.hpp"

#include "Mayhem/Core/Timestep.h"

namespace Mayhem
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity createEntity(const std::string& name = std::string());

		void onUpdate(Timestep ts);

	private:
		entt::registry mRegistry;

		friend class Entity;
	};
}