#include "Sandbox.h"

#include <Aquarius.h>

Sandbox::Sandbox()
	: Aquarius::Application("Sandbox")
{}

Aquarius::Application::ApplicationPtr createApplication()
{
	return std::make_unique<Sandbox>();
}
