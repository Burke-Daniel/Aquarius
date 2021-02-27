#pragma once

#include "Aquarius/Core/Log.h"
#include "Aquarius/Core/Input.h"
#include "Event.h"

#include <GLFW/glfw3.h>

namespace Aquarius {

    class MouseMoved : public Event
    {
    public:
        MouseMoved(const double x, const double y)
            : m_XPosition(x), m_YPosition(y) {}

        double GetXPosition() const
        {
            return m_XPosition;
        }

        double GetYPosition() const
        {
            return m_YPosition;
        }

        EVENT_TYPE(InputEvent | MouseEvent | MouseMovedEvent)
        AQ_CORE_INFO("MouseMovedEvent: X Position: %v  Y Position: %v", m_XPosition, m_YPosition);

    private:
        double m_XPosition, m_YPosition;
    };

    class MouseScrolled : public Event
    {
    public:
        MouseScrolled(const double x, const double y)
            : m_XOffset(x), m_YOffset(y) {}

        double GetXOffset() const
        {
            return m_XOffset;
        }

        double GetYOffset() const
        {
            return m_YOffset;
        }

        EVENT_TYPE(InputEvent | MouseEvent | MouseScrolled)
        AQ_CORE_INFO("MouseScrolledEvent: X Offset: %v  Y Offset: %v", m_XOffset, m_YOffset);

    private:
        double m_XOffset, m_YOffset;
    };

    class MouseButton : public Event
    {
    public:
        MouseCode GetMouseButtonCode() const
        {
            return m_ButtonCode;
        }

    protected:
        MouseButton(const MouseCode button)
            : m_ButtonCode(button) {}

        MouseCode m_ButtonCode;
    };

    class MouseButtonPressed : public MouseButton
    {
    public:
        MouseButtonPressed(const MouseCode button)
            : MouseButton(button) {}

            AQ_CORE_INFO("MouseButtonPressed: %v", m_ButtonCode)

            EVENT_TYPE(InputEvent


    };




} // namespace Aquarius
