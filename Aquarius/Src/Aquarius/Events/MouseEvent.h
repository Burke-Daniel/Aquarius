#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>

#define CREATE_MOUSE_EVENT(event) \
    class event : public Event<MouseEvents> \
    { \
    public: \
        event() : Event<MouseEvents>(MouseEvents::event) {} \
    }


namespace Aquarius {

    enum class MouseEvents
    {
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, MouseInWindow
    };

    CREATE_MOUSE_EVENT(MouseButtonPressed);
    CREATE_MOUSE_EVENT(MouseButtonReleased);
    CREATE_MOUSE_EVENT(MouseMoved);
    CREATE_MOUSE_EVENT(MouseScrolled);
    CREATE_MOUSE_EVENT(MouseInWindow);

} // namespace Aquarius
