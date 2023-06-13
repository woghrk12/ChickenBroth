#include "Application.h"
#include "ChickenBroth/Events/ApplicationEvent.h"
#include "ChickenBroth/Log.h"

namespace ChickenBroth
{
	Application::Application() {}

	Application::~Application() {}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if(e.IsInCategory(EventCategoryApplication)) CB_TRACE(e);
		if (e.IsInCategory(EventCategoryInput)) CB_TRACE(e);

		while (true);
	}
}