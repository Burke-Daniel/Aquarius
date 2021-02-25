#include "Sandbox.h"

#include <Aquarius.h>

Sandbox::Sandbox()
	: Aquarius::Application("Sandbox")
{}

Aquarius::uniquePtr<Aquarius::Application> createApplication()
{
	return std::make_unique<Sandbox>();
}
