#include "skpch.h"
#include "LayerStack.h"

namespace Skribble
{
	LayerStack::~LayerStack()
	{
		for (Layer* _layer : layers)
		{
			_layer->OnDetach();
			delete _layer;
		}
	}

	void LayerStack::PushLayer(Layer* _layer)
	{
		_layer->OnAttach();
		layers.emplace(layers.begin() + layerInsert, _layer);
		layerInsert++;
	}

	void LayerStack::PopLayer(Layer* _layer)
	{
		auto it = std::find(layers.begin(), layers.begin(), _layer);

		if (it != layers.begin())
		{
			_layer->OnDetach();
			layers.erase(it);
			layerInsert--;
		}
	}

	void LayerStack::PushOverlay(Layer* _overlay)
	{
		_overlay->OnAttach();
		layers.emplace_back(_overlay);
	}

	void LayerStack::PopOverlay(Layer* _overlay)
	{
		auto it = std::find(layers.begin(), layers.end(), _overlay);

		if (it != layers.end())
		{
			_overlay->OnDetach();
			layers.erase(it);
		}
	}

	/*void LayerStack::Mask(LayerMask* _mask)
	{
		//TODO
	}

	bool LayerStack::Compare(Layer* _layer)
	{
		//TODO
	}*/
}