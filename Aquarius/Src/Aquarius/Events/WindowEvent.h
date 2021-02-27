#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    enum class WindowEvents
            {
        WindowClosedEvent, WindowResizedEvent, WindowFocusedEvent, WindowMovedEvent
            };

    class WindowClosed : public Event<WindowEvents>
    {
    public:
        WindowClosed() : Event<WindowEvents>(WindowEvents::WindowClosedEvent) {};
    };

    class WindowResized : public Event<WindowEvents>
    {
    public:
        WindowResized() : Event<WindowEvents>(WindowEvents::WindowResizedEvent) {};
    };

    class WindowFocused : public Event<WindowEvents>
    {
    public:
        WindowFocused() : Event<WindowEvents>(WindowEvents::WindowFocusedEvent) {};
    };

    class WindowMoved : public Event<WindowEvents>
    {
    public:
        WindowMoved() : Event<WindowEvents>(WindowEvents::WindowMovedEvent) {};
    };

} // namespace Aquarius
