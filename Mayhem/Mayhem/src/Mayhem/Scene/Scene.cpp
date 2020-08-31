#include "mpch.h"
#include "Scene.h"

#include "Components.h"
#include "Mayhem/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Mayhem
{

	Scene::Scene()
	{
 
	}

	Scene::~Scene()
	{

	}

	entt::entity Scene::createEntity()
	{
		return mRegistry.create();
	}

	void Scene::onUpdate(Timestep ts)
	{
		auto group = mRegistry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::drawQuad(transform.Transform, sprite.Color);
		}
	}
}