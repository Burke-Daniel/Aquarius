#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    class KeyEvent : public Event
    {
    public:

        int getCode()
        {
            return m_keyCode;
        }

    protected:
        int m_keyCode;

        KeyEvent(int keyCode) : m_keyCode(keyCode) {}
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode) : KeyEvent(keyCode) {}

        EVENT_TYPE(KeyPressedEvent)

        void logEvent()
        {
            AQ_CORE_TRACE("KeyPressedEvent: %v",m_keyCode);
        }
    };

    class KeyRepeatedEvent : public KeyEvent
    {
    public:
        KeyRepeatedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        EVENT_TYPE(KeyRepeatedEvent)

        void logEvent()
        {
            AQ_CORE_TRACE("KeyRepeatedEvent: %v", m_keyCode);
        }

    protected:
        int m_repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        EVENT_TYPE(KeyReleasedEvent)

        void logEvent()
        {
            AQ_CORE_TRACE("KeyReleasedEvent: %v",m_keyCode);
        }
    };

} // namespace Aquarius
