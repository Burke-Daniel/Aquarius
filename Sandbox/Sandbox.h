#pragma once

#include "Aquarius/Core/Application.h"

class Sandbox : public Aquarius::Application
{
public:
	Sandbox();
};

Aquarius::Application::ApplicationPtr createApplication()
{
	return std::make_unique<Sandbox>();
}