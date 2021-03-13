#pragma once

#include "Event.h"
#include "Aquarius/Core/Input.h"
#include "Aquarius/Core/Log.h"


namespace Aquarius {

    class KeyEvent : public Event
    {
    public:

        Input::KeyCode getCode() const
        {
            return m_keyCode;
        }

    protected:
        Input::KeyCode m_keyCode;

        KeyEvent(int keyCode) : m_keyCode(static_cast<Input::KeyCode>(keyCode)) {}
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode) : KeyEvent(keyCode) {}

        EVENT_TYPE(KeyPressedEvent)

        void logEvent () const override
        {
            AQ_CORE_TRACE("KeyPressedEvent: %v",static_cast<int>(m_keyCode));
        }
    };

    class KeyRepeatedEvent : public KeyEvent
    {
    public:
        KeyRepeatedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        EVENT_TYPE(KeyRepeatedEvent)

        void logEvent() const override
        {
            AQ_CORE_TRACE("KeyRepeatedEvent: %v", static_cast<int>(m_keyCode));
        }

        int getRepeatCount() const
        {
            return m_repeatCount;
        }

    private:
        int m_repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        EVENT_TYPE(KeyReleasedEvent)

        void logEvent() const override
        {
            AQ_CORE_TRACE("KeyReleasedEvent: %v",static_cast<int>(m_keyCode));
        }
    };

} // namespace Aquarius
