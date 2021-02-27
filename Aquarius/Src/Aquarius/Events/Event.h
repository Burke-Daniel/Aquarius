#pragma once

#include "Aquarius/Core/Log.h"

#include <GLFW/glfw3.h>

// Use Bit Masking to allow for the use of Bitwise Operations to filter events based on requirements
#define BIT(x) (1 << x)


namespace Aquarius {

    // The below Macro is purely for convenience when assigning the event type
    #define EVENT_TYPE(type) virtual int GetEventType() const override { return type;}

    class Event
    {
    public:
        virtual ~Event() = default;
        virtual int GetEventType() const = 0;
        bool IsEventHandled = false;

        bool SameEventType(EventType type)
        {
            // Bitwise AND
            bool result = GetEventType() & type;

            // Can log result here if wanted.

            return result;
        }

        enum EventType
        {
            None = 0,

            // General Input (Keyboard or Mouse)
            InputEvent = BIT(0),

            // Keyboard Events
            KeyboardEvent = BIT(1),
            KeyPressedEvent = BIT(2),
            KeyRepeatedEvent = BIT(3),
            KeyReleasedEvent = BIT(4),

            // Mouse Events
            MouseEvent = BIT(5),
            MouseButtonPressedEvent = BIT(6),
            MouseButtonReleasedEvent = BIT(7),
            MouseMovedEvent = BIT(8),
            MouseInWindowEvent = BIT(9),
            MouseScrolledEvent = BIT(10),

            // Window Events
            WindowEvent = BIT(11),
            WindowClosedEvent = BIT(12),
            WindowResizedEvent = BIT(13),
            WindowFocusedEvent = BIT(14),
            WindowMovedEvent = BIT(15)
        };
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        // Implement

    private:
        Event& m_Event;
    };

} // namespace Aquarius
