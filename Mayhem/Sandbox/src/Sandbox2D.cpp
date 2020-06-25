#include "Sandbox2D.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public :
	Timer(const char* name, Fn&& func)
		:mName(name), mFunc(func), mStopped(false)
	{
		mStartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!mStopped)
			stop();
	}

	void stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		mStopped = true;

		float duration = (end - start) * 0.001f;
		mFunc({ mName, duration });
	}


private:
	const char* mName; 
	Fn mFunc;
	std::chrono::time_point<std::chrono::steady_clock> mStartTimePoint;
	bool mStopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { mProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D()
	:Layer("Sandox2D"), mCameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::onAttatch()
{
	mTailsTexture = Mayhem::Texture2D::create("assets/textures/Tails.png");
}

void Sandbox2D::onDetatch()
{

}

void Sandbox2D::onUpdate(Mayhem::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::onUpdate");

	//Update
	{
		PROFILE_SCOPE("CameraController::onUpdate");
		mCameraController.onUpdate(ts);
	}

	//Render
	{
		PROFILE_SCOPE("Render Prep");
		Mayhem::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mayhem::RenderCommand::clear();
	}
	
	{
		PROFILE_SCOPE("Render Draw");

		Mayhem::Renderer2D::beginScene(mCameraController.getCamera());
		Mayhem::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Mayhem::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Mayhem::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, mTailsTexture);
		Mayhem::Renderer2D::endScene();
	}
}

void Sandbox2D::onEvent(Mayhem::Event& e)
{
	mCameraController.onEvent(e);
}

void Sandbox2D::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));

	for (auto& result : mProfileResults)
	{
		char label[50];
		
		strcpy(label, "  %.3fms ");
		strcat(label, result.name);

		ImGui::Text(label, result.time);
	}

	mProfileResults.clear();

	ImGui::End();
}
