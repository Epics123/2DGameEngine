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
		void onViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry mRegistry;
		uint32_t mViewportWidth = 0, mViewportHeight = 0;

		friend class Entity;
	};
}