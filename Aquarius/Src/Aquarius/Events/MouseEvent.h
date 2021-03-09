#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float xCoordinate, float yCoordinate)
                : m_XCoordinate(xCoordinate), m_YCoordinate(yCoordinate) {}

        EVENT_TYPE(MouseMovedEvent)

        void logEvent()
        {
            AQ_CORE_TRACE("MouseMovedEvent: %v, %v", m_XCoordinate, m_YCoordinate);
        }

        float getXCoordinate()
        {
            return m_XCoordinate;
        }

        float getYCoordinate()
        {
            return m_YCoordinate;
        }

    private:
        float m_XCoordinate;
        float m_YCoordinate;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xCoordinate, float yCoordinate)
                : m_XCoordinate(xCoordinate), m_YCoordinate(yCoordinate) {}

        EVENT_TYPE(MouseScrolledEvent)

        void logEvent()
        {
            AQ_CORE_TRACE("MouseScrolledEvent: %v, %v", m_XCoordinate, m_YCoordinate);
        }

        float getXCoordinate()
        {
            return m_XCoordinate;
        }

        float getYCoordinate()
        {
            return m_YCoordinate;
        }

    private:
        float m_XCoordinate;
        float m_YCoordinate;
    };

    class MouseButtonEvent : public Event
    {
    public:
        int getCode()
        {
            return m_buttonCode;
        }

    protected:
        int m_buttonCode;

        MouseButtonEvent(int buttonCode) : m_buttonCode(buttonCode) {}
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}

        EVENT_TYPE(MouseButtonPressedEvent)

        void logEvent()
        {
            AQ_CORE_TRACE("MouseButtonPressedEvent: %v", m_buttonCode);
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}

        EVENT_TYPE(MouseButtonReleasedEvent)

        void logEvent()
        {
            AQ_CORE_TRACE("MouseButtonReleasedEvent: %v", m_buttonCode);
        }
    };

    class MouseInWindowEvent : public Event
    {
    public:
        MouseInWindowEvent(int inWindow) : m_inWindow(inWindow) {}

        EVENT_TYPE(MouseInWindowEvent)

        void logEvent()
        {
            if (inWindow() == 1)
            {
                AQ_CORE_TRACE("Cursor is in the window.");
            }

            else
            {
                AQ_CORE_TRACE("Cursor is not in the window.");
            }
        }

        int inWindow()
        {
            return m_inWindow;
        }

    private:
        int m_inWindow;
    };

} // namespace Aquarius
