#pragma once

#include "Aquarius/Core/Utility.h"

#include <deque>
#include <string>


namespace Aquarius {

	class Event;
	class Layer;

	using LayerStack = std::deque<uniquePtr<Layer>>;

	class Layer
	{
	public:
		Layer() = delete;
		virtual ~Layer() { onDestruction(); };

		virtual void onCreation() {};
		virtual void onEvent(const Event& event) {};
		virtual void onUpdate(timeDelta_t time) {};
		virtual void onDestruction() {};

		const std::string& getLayerName() const { return m_layerName; }
		bool isActive() const { return m_active; }
		void activate() { m_active = true; }
		void deactivate() { m_active = false; }

	protected:
		Layer(const std::string& layerName, bool isActive)
			: m_layerName(layerName), m_active(isActive)
		{}

	private:
		const std::string m_layerName;
		bool m_active;
	};

} // namespace Aquarius
