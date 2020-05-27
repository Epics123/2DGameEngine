#include <Mayhem.h>

class ExampleLayer : public Mayhem::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void onUpdate() override
	{
		MH_INFO("ExampleLayer::Update");
	}

	void onEvent(Mayhem::Event& event)
	{
		MH_TRACE("{0}", event);
	}
};

class Sandbox : public Mayhem::Application
		
			{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
		pushOverlay(new Mayhem::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Mayhem::Application* Mayhem::createApplication()
{
	return new Sandbox();
}