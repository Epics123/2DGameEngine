#pragma once

#include "entt.hpp"

#include "Mayhem/Core/Timestep.h"

namespace Mayhem
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity createEntity();

		//TEMP
		entt::registry& Reg() { return mRegistry; }

		void onUpdate(Timestep ts);

	private:
		entt::registry mRegistry;
	};
}