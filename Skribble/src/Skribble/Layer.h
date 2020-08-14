#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Skribble
{
	class SKRIBBLE_API Layer
	{
	public:
		Layer(const std::string& _name = "New layer");
		virtual ~Layer() = default;

		virtual void Update() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnEvent(Event& _event) {}
		
		inline const std::string& GetName() const { return name; }

	protected:
		std::string name;
	};
}