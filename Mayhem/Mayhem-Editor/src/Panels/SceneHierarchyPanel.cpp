#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

#include "Mayhem/Scene/Components.h"

namespace Mayhem
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		setContext(context);
	}

	void SceneHierarchyPanel::setContext(const Ref<Scene>& context)
	{
		mContext = context;
	}

	void SceneHierarchyPanel::onImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		mContext->mRegistry.each([&](auto entityID)
		{
			Entity entity{ entityID, mContext.get() };
			drawEntityNode(entity);
		});

		ImGui::End();
	}

	void SceneHierarchyPanel::drawEntityNode(Entity entity)
	{
		auto& tag = entity.getComponent<TagComponent>().Tag;
		
		ImGuiTreeNodeFlags flags = ((mSelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			mSelectionContext = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
		}

	}

}