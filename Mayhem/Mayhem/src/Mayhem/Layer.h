#pragma once

#include "Mayhem/Core.h"
#include "Events/Event.h"

namespace Mayhem
{
	class MAYHEM_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttatch() {}
		virtual void onDetatch() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return mDebugName; }

	protected:
		std::string mDebugName;
	};
}