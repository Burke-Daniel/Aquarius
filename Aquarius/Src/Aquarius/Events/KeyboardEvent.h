#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>

#define CREATE_KEYBOARD_EVENT(event) \
    class event : public Event<KeyboardEvents> \
    { \
    public: \
        event() : Event<KeyboardEvents>(KeyboardEvents::event) {} \
    }

namespace Aquarius {

    enum class KeyboardEvents
    {
        KeyPressed, KeyRepeated, KeyReleased,
    };

    CREATE_KEYBOARD_EVENT(KeyPressed);
    CREATE_KEYBOARD_EVENT(KeyRepeated);
    CREATE_KEYBOARD_EVENT(KeyReleased);

} // namespace Aquarius
