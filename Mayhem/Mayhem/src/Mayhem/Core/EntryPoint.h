#pragma once
#include <stdio.h>

#ifdef MH_PLATFORM_WINDOWS

extern Mayhem::Application* Mayhem::createApplication();

int main(int argc, char** argv)
{
	Mayhem::Log::init();
	MH_CORE_WARN("Log initialized");
	int a = 5;
	MH_INFO("Hello! Var = {0}", a);

	auto app = Mayhem::createApplication();
	app->run();
	delete app;

	return 0;
}

#endif // MH_PLATFORM_WINDOWS
