#pragma once

#include "Mayhem/Core/Core.h"
#include "Layer.h"

namespace Mayhem
{
	class MAYHEM_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
		std::vector<Layer*>::iterator end() { return mLayers.end(); }

	private:
		std::vector<Layer*> mLayers;
		unsigned int mLayerInsertIndex = 0;
	};
}