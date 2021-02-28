#pragma once

#include "Event.h"
#include "Aquarius/Core/Log.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    enum class KeyboardEvents
            {
        KeyPressedEvent, KeyRepeatedEvent, KeyReleasedEvent,
    };

    class KeyPressed : public Event<KeyboardEvents>
    {
    public:
        KeyPressed() : Event<KeyboardEvents>(KeyboardEvents::KeyPressedEvent) {};
    };

    class KeyRepeated : public Event<KeyboardEvents>
    {
    public:
        KeyRepeated() : Event<KeyboardEvents>(KeyboardEvents::KeyRepeatedEvent) {};
    };

    class KeyReleased : public Event<KeyboardEvents>
    {
    public:
        KeyReleased() : Event<KeyboardEvents>(KeyboardEvents::KeyReleasedEvent) {};
    };

} // namespace Aquarius
