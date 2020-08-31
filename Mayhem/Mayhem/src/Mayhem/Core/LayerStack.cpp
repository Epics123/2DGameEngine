#include "mpch.h"
#include "LayerStack.h"

namespace Mayhem
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : mLayers)
		{
			layer->onDetatch();
			delete layer;
		}		
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		mLayers.emplace(mLayers.begin() + mLayerInsertIndex, layer);
		mLayerInsertIndex++;
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		mLayers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(mLayers.begin(), mLayers.begin() + mLayerInsertIndex, layer);
		if (it != mLayers.begin() + mLayerInsertIndex)
		{
			layer->onDetatch();
			mLayers.erase(it);
			mLayerInsertIndex--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(mLayers.begin() + mLayerInsertIndex, mLayers.end(), overlay);
		if (it != mLayers.end())
		{
			overlay->onDetatch();
			mLayers.erase(it);
		}
	}
}