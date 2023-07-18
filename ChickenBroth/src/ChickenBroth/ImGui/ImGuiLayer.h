#pragma once

#include "ChickenBroth/Layer.h"
#include "ChickenBroth/Events/ApplicationEvent.h"
#include "ChickenBroth/Events/KeyEvent.h"
#include "ChickenBroth/Events/MouseEvent.h"

namespace ChickenBroth
{
	class CHICKEN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}