#pragma once

#include <Aquarius.h>

class Sandbox : public Aquarius::Application
{
public:
	Sandbox();
};

Aquarius::Application::ApplicationPtr createApplication();
