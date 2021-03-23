#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Skribble
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* _layer);
		void PopLayer(Layer* _layer);

		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
		
	private:
		std::vector<Layer*> layers;
		unsigned int layerInsert = 0;
	};
}