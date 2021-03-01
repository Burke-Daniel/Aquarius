#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    enum class KeyboardEvents
    {
        KeyPressedEvent, KeyRepeatedEvent, KeyReleasedEvent,
    };

    class KeyPressedEvent : public Event<KeyboardEvents>
    {
    public:
        KeyPressedEvent() : Event<KeyboardEvents>(KeyboardEvents::KeyPressedEvent, m_Code, 0,0) {};
    };

    class KeyRepeatedEvent : public Event<KeyboardEvents>
    {
    public:
        KeyRepeatedEvent() : Event<KeyboardEvents>(KeyboardEvents::KeyRepeatedEvent, m_Code, 0, 0) {};
    };

    class KeyReleasedEvent : public Event<KeyboardEvents>
    {
    public:
        KeyReleasedEvent() : Event<KeyboardEvents>(KeyboardEvents::KeyReleasedEvent, m_Code, 0, 0) {};
    };

} // namespace Aquarius
