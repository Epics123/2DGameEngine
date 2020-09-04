#pragma once

#include "Mayhem/Core/Core.h"
#include "Mayhem/Core/Log.h"
#include "Mayhem/Scene/Scene.h"
#include "Mayhem/Scene/Entity.h"

namespace Mayhem
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void setContext(const Ref<Scene>& context);

		void onImGuiRender();

	private:
		void drawEntityNode(Entity entity);

	private:
		Ref<Scene> mContext;
		Entity mSelectionContext;
	};
}