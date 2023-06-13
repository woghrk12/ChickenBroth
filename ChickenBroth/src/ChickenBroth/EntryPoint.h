#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern ChickenBroth::Application* ChickenBroth::CreateApplication();

int main(int argc, char** argv)
{
	auto app = ChickenBroth::CreateApplication();
	app->Run();
	delete app;
}

#endif // CB_PLATFORM_WINDOWS
