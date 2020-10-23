#include "EditorLayer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Mayhem
{
	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), mCameraController(1280.0f / 720.0f)
	{

	}

	void EditorLayer::onAttatch()
	{
		mTailsTexture = Texture2D::create("assets/textures/Tails.png");
		mSpriteSheet = Texture2D::create("assets/game/textures/RPGpack_sheet_2X.png");

		mTextureStairs = SubTexture2D::createFromCoords(mSpriteSheet, { 7, 6 }, { 128, 128 });
		mTextureTree = SubTexture2D::createFromCoords(mSpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

		FrameBufferSpec fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		mFrameBuffer = FrameBuffer::create(fbSpec);

		mActiveScene = CreateRef<Scene>();

		//Entity
		auto square = mActiveScene->createEntity("Green Square");
		square.addComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

		auto redSquare = mActiveScene->createEntity("Red Square");
		redSquare.addComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		mSquareEntity = square;

		mCameraEntity = mActiveScene->createEntity("Camera Entity");
		mCameraEntity.addComponent<CameraComponent>();

		mSecondCamera = mActiveScene->createEntity("Clip Space Camera Entity");
		auto& cc = mSecondCamera.addComponent<CameraComponent>();
		cc.Primary = false;

		class CameraController : public ScriptableEntity
		{
		public:
			void onCreate()
			{		
				auto& transform = getComponent<TransformComponent>().Transform;
				transform[3][0] = rand() % 10 - 5.0f;
			}

			void onDestroy()
			{

			}

			void onUpdate(Timestep ts)
			{
				auto& transform = getComponent<TransformComponent>().Transform;
				float speed = 5.0f;

				if (Input::isKeyPressed(KeyCode::A))
					transform[3][0] -= speed * ts;
				if (Input::isKeyPressed(KeyCode::D))
					transform[3][0] += speed * ts;
				if (Input::isKeyPressed(KeyCode::W))
					transform[3][1] += speed * ts;
				if (Input::isKeyPressed(KeyCode::S))
					transform[3][1] -= speed * ts;
			}
		};

		mCameraEntity.addComponent<NativeScriptComponent>().bind<CameraController>();
		mSecondCamera.addComponent<NativeScriptComponent>().bind<CameraController>();

		mSceneHierarchyPanel.setContext(mActiveScene);
	}

	void EditorLayer::onDetatch()
	{

	}

	void EditorLayer::onUpdate(Timestep ts)
	{
		//Resize
		mFrameBuffer->resize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
		mCameraController.onResize(mViewportSize.x, mViewportSize.y);

		mActiveScene->onViewportResize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);

		//Update
		if(mViewportFocused)
			mCameraController.onUpdate(ts);

		//Render
		Renderer2D::resetStats();
		mFrameBuffer->bind();
		RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::clear();
		
		//Update Scene
		mActiveScene->onUpdate(ts);

		mFrameBuffer->unbind();
	}

	void EditorLayer::onEvent(Mayhem::Event& e)
	{
		mCameraController.onEvent(e);
	}

	void EditorLayer::onImGuiRender()
	{
		static bool docspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &docspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Mayhem::Application::getInstance().close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		mSceneHierarchyPanel.onImGuiRender();

		ImGui::Begin("Settings");

		auto stats = Mayhem::Renderer2D::getStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());

		if (mSquareEntity)
		{
			ImGui::Separator();
			auto& tag = mSquareEntity.getComponent<TagComponent>().Tag;
			ImGui::Text("%s", tag.c_str());

			auto& squareColor = mSquareEntity.getComponent<SpriteRendererComponent>().Color;
			ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
		}

		ImGui::DragFloat3("Camera Transform", glm::value_ptr(mCameraEntity.getComponent<TransformComponent>().Transform[3]));

		if (ImGui::Checkbox("Camera A", &mPrimaryCamera))
		{
			mCameraEntity.getComponent<CameraComponent>().Primary = mPrimaryCamera;
			mSecondCamera.getComponent<CameraComponent>().Primary = !mPrimaryCamera;
		}

		{
			auto& camera = mSecondCamera.getComponent<CameraComponent>().Camera;
			float orthoSize = camera.getOrthographicSize();
			if (ImGui::DragFloat("SecondCamera Ortho Size", &orthoSize))
			{
				camera.setOrthographicSize(orthoSize);
			}
		}
		
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		
		mViewportFocused = ImGui::IsWindowFocused();
		mViewportHovered = ImGui::IsWindowHovered();
		Application::getInstance().getImGuiLayer()->blockEvents(!mViewportFocused || !mViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (mViewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			mFrameBuffer->resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			mViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			mCameraController.onResize(viewportPanelSize.x, viewportPanelSize.y);
		}

		//MH_WARN("Viewport Size: {0}, {1}", viewportPanelSize.x, viewportPanelSize.y);

		uint32_t textureID = mFrameBuffer->getColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ mViewportSize.x, mViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();

		//Dockspace End
		ImGui::End();

	}
}


