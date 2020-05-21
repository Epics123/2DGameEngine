#include <Mayhem.h>

class Sandbox : public Mayhem::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Mayhem::Application* Mayhem::createApplication()
{
	return new Sandbox();
}