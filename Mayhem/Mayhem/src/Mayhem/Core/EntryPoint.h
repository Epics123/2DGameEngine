#pragma once
#include <stdio.h>

#ifdef MH_PLATFORM_WINDOWS

extern Mayhem::Application* Mayhem::createApplication();

int main(int argc, char** argv)
{
	Mayhem::Log::init();

	MH_PROFILE_BEGIN_SESSION("Startup", "MayhemProfile-Startup.json");
	auto app = Mayhem::createApplication();
	MH_PROFILE_END_SESSION();

	MH_PROFILE_BEGIN_SESSION("Runtime", "MayhemProfile-Runtime.json");
	app->run();
	MH_PROFILE_END_SESSION();

	MH_PROFILE_BEGIN_SESSION("Shutdown", "MayhemProfile-Shutdown.json");
	delete app;
	MH_PROFILE_END_SESSION();

	return 0;
}

#endif // MH_PLATFORM_WINDOWS
