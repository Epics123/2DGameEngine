#include "mpch.h"
#include "Entity.h"

namespace Mayhem
{

	Entity::Entity(entt::entity handle, Scene* scene)
		:mEntityHandle(handle), mScene(scene)
	{

	}

}