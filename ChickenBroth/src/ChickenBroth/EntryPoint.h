#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern ChickenBroth::Application* ChickenBroth::CreateApplication();

int main(int argc, char** argv)
{
	ChickenBroth::Log::Init();
	CB_CORE_WARN("Initialized Log!");
	CB_INFO("Hello!");

	auto app = ChickenBroth::CreateApplication();
	app->Run();
	delete app;
}

#endif // CB_PLATFORM_WINDOWS
