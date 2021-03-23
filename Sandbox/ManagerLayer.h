#pragma once

#include "Aquarius.h"

#include <vector>


class ManagerLayer : public Aquarius::Layer
{
public:
	ManagerLayer(std::vector<Aquarius::Layer*> layer);

	virtual void onCreation() override;
	virtual void onEvent(const Aquarius::Event& event) override;
	
	void AddManagedLayer(Aquarius::Layer* layer) { m_ManagedLayers.push_back(layer); };

private:
	std::vector<Aquarius::Layer*> m_ManagedLayers;
	size_t m_ActiveLayerIndex;
};
