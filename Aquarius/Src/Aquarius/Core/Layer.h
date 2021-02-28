#pragma once

#include "Aquarius/Core/Utility.h"

#include <deque>
#include <string>


namespace Aquarius {

	class Event;
	class Layer;

	using LayerStack = std::deque<uniquePtr<Layer>>;
	using timeDelta_t = float;

	class Layer
	{
	public:
		virtual ~Layer() { onDestruction(); };

		virtual void onCreation() {};
		virtual void onEvent(Event& event) {};
		virtual void onUpdate(timeDelta_t time) {};
		virtual void onDestruction() {};

	protected:
		Layer(const std::string& layerName)
			: m_layerName(layerName)
		{}

	private:
		const std::string m_layerName;
	};

} // namespace Aquarius
