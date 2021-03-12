#pragma once

#include "Event.h"


namespace Aquarius {

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float xPosition, float yPosition)
                : m_XPosition(xPosition), m_YPosition(yPosition) {}

        EVENT_TYPE(MouseMovedEvent)

        void logEvent() override
        {
            AQ_CORE_TRACE("MouseMovedEvent: %v, %v", m_XPosition, m_YPosition);
        }

        float getXCoordinate()
        {
            return m_XPosition;
        }

        float getYCoordinate()
        {
            return m_YPosition;
        }

    private:
        float m_XPosition;
        float m_YPosition;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
                : m_XOffset(xOffset), m_YOffset(yOffset) {}

        EVENT_TYPE(MouseScrolledEvent)

        void logEvent() override
        {
            AQ_CORE_TRACE("MouseScrolledEvent: %v, %v", m_XOffset, m_YOffset);
        }

        float getXOffset()
        {
            return m_XOffset;
        }

        float getYOffset()
        {
            return m_YOffset;
        }

    private:
        float m_XOffset;
        float m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        Input::MouseButtonCode getCode()
        {
            return m_buttonCode;
        }

    protected:
        Input::MouseButtonCode m_buttonCode;

        MouseButtonEvent(int buttonCode) : m_buttonCode(static_cast<Input::MouseButtonCode>(buttonCode)) {}
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}

        EVENT_TYPE(MouseButtonPressedEvent)

        void logEvent() override
        {
            AQ_CORE_TRACE("MouseButtonPressedEvent: %v", static_cast<int>(m_buttonCode));
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}

        EVENT_TYPE(MouseButtonReleasedEvent)

        void logEvent() override
        {
            AQ_CORE_TRACE("MouseButtonReleasedEvent: %v", static_cast<int>(m_buttonCode));
        }
    };

    class MouseInWindowEvent : public Event
    {
    public:
        MouseInWindowEvent(int inWindow) : m_inWindow(static_cast<bool>(inWindow)) {}

        EVENT_TYPE(MouseInWindowEvent)

        void logEvent() override
        {
            if (inWindow())
            {
                AQ_CORE_TRACE("Cursor is in the window.");
            }

            else
            {
                AQ_CORE_TRACE("Cursor is not in the window.");
            }
        }

        bool inWindow()
        {
            return m_inWindow;
        }

    private:
        bool m_inWindow;
    };

} // namespace Aquarius
