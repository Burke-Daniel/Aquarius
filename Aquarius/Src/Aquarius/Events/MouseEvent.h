#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    enum class MouseEvents
    {
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent, MouseInWindowEvent
    };

    class MouseButtonPressed : public Event<MouseEvents>
    {
    public:
        MouseButtonPressed() : Event<MouseEvents>(MouseEvents::MouseButtonPressedEvent) {};
    };

    class MouseButtonReleased : public Event<MouseEvents>
    {
    public:
        MouseButtonReleased() : Event<MouseEvents>(MouseEvents::MouseButtonReleasedEvent) {};
    };

    class MouseMoved : public Event<MouseEvents>
    {
    public:
        MouseMoved() : Event<MouseEvents>(MouseEvents::MouseMovedEvent) {};
    };

    class MouseScrolled : public Event<MouseEvents>
    {
    public:
        MouseScrolled() : Event<MouseEvents>(MouseEvents::MouseScrolledEvent) {};
    };

    class MouseInWindow : public Event<MouseEvents>
    {
    public:
        MouseInWindow() : Event<MouseEvents>(MouseEvents::MouseInWindowEvent) {};
    };

} // namespace Aquarius
