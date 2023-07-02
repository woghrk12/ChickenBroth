#include <ChickenBroth.h>

#include "imgui/imgui.h"

class ExampleLayer : public ChickenBroth::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override { if (ChickenBroth::Input::IsKeyPressed(CB_KEY_TAB)) { CB_TRACE("Tab key is pressed (poll)!"); }; }

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(ChickenBroth::Event& event) override 
	{
		if (event.GetEventType() == ChickenBroth::EventType::KeyPressed)
		{
			ChickenBroth::KeyPressedEvent& e = (ChickenBroth::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CB_KEY_TAB) { CB_TRACE("Tab key is pressed (event)!"); }
			CB_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public ChickenBroth::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer()); ;
	}

	~Sandbox() {}
};

ChickenBroth::Application* ChickenBroth::CreateApplication() { return new Sandbox(); }