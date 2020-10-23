#pragma once
#include <stdio.h>

#ifdef MH_PLATFORM_WINDOWS

extern Mayhem::Application* Mayhem::createApplication();

int main(int argc, char** argv)
{
	Mayhem::Log::init();

	auto app = Mayhem::createApplication();
	app->run();
	delete app;

	return 0;
}

#endif // MH_PLATFORM_WINDOWS
