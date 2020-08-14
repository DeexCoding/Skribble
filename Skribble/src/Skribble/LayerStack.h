#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Skribble
{
	class SKRIBBLE_API LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* _layer);
		void PullLayer(Layer* _layer);

		void PushOverlay(Layer* overlay);
		void PullOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
		
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;
	};
}