#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>

#define CREATE_WINDOW_EVENT(event) \
    class event : public Event<WindowEvents> \
    { \
    public: \
        event() : Event<WindowEvents>(WindowEvents::event) {} \
    }

namespace Aquarius {

    enum class WindowEvents
    {
        WindowClosed, WindowResized, WindowFocused, WindowMoved
    };

    CREATE_WINDOW_EVENT(WindowClosed);
    CREATE_WINDOW_EVENT(WindowResized);
    CREATE_WINDOW_EVENT(WindowFocused);
    CREATE_WINDOW_EVENT(WindowMoved);

} // namespace Aquarius
