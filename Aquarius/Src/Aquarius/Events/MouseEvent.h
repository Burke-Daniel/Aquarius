#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    enum class MouseEvents
    {
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent, MouseInWindowEvent
    };

    class MouseButtonPressedEvent : public Event<MouseEvents>
    {
    public:
        MouseButtonPressedEvent() : Event<MouseEvents>(MouseEvents::MouseButtonPressedEvent, m_Code, 0, 0) {};
    };

    class MouseButtonReleasedEvent : public Event<MouseEvents>
    {
    public:
        MouseButtonReleasedEvent() : Event<MouseEvents>(MouseEvents::MouseButtonReleasedEvent, m_Code, 0, 0) {};
    };

    class MouseMovedEvent : public Event<MouseEvents>
    {
    public:
        MouseMovedEvent() : Event<MouseEvents>(MouseEvents::MouseMovedEvent, 0, m_xAxis, m_yAxis) {};
    };

    class MouseScrolledEvent : public Event<MouseEvents>
    {
    public:
        MouseScrolledEvent() : Event<MouseEvents>(MouseEvents::MouseScrolledEvent, 0, m_xAxis, m_yAxis) {};
    };

    class MouseInWindowEvent : public Event<MouseEvents>
    {
    public:
        MouseInWindowEvent() : Event<MouseEvents>(MouseEvents::MouseInWindowEvent, m_Code, 0, 0) {};
    };

} // namespace Aquarius
