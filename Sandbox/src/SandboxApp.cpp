#include <ChickenBroth.h>

class Sandbox : public ChickenBroth::Application
{
public:
	Sandbox() {}

	~Sandbox() {}
};

ChickenBroth::Application* ChickenBroth::CreateApplication() { return new Sandbox(); }