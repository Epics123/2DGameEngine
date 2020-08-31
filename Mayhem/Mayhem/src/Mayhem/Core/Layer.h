#pragma once

#include "Mayhem/Core/Core.h"
#include "Mayhem/Core/Timestep.h"
#include "Mayhem/Events/Event.h"

namespace Mayhem
{
	class MAYHEM_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttatch() {}
		virtual void onDetatch() {}
		virtual void onUpdate(Timestep timestep) {}
		virtual void onImGuiRender(){}
		virtual void onEvent(Event& event) {}

		const std::string& getName() const { return mDebugName; }

	protected:
		std::string mDebugName;
	};
}