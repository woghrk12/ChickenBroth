#include <ChickenBroth.h>

class ExampleLayer : public ChickenBroth::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override { CB_INFO("ExampleLayer::Update"); }

	void OnEvent(ChickenBroth::Event& event) override { CB_TRACE("{0}", event); }
};

class Sandbox : public ChickenBroth::Application
{
public:
	Sandbox() { PushLayer(new ExampleLayer()); }

	~Sandbox() {}
};

ChickenBroth::Application* ChickenBroth::CreateApplication() { return new Sandbox(); }