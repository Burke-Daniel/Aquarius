#pragma once


namespace Aquarius {

    enum class eventType
    {
        None = 0,
        KeyPressedEvent, KeyRepeatedEvent, KeyReleasedEvent,
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent, MouseInWindowEvent
    };

#define EVENT_TYPE(type) static eventType getStaticType() { return eventType::type; }\
                                                            virtual eventType getEventType() const override { return getStaticType(); }\
                                                            virtual const char* getName() const override { return #type; }

    class Event
    {
    public:
        virtual eventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        bool m_Handled = false;
        virtual ~Event() = default;

        bool isHandled()
        {
            return m_Handled;
        };
    };

} // namespace Aquarius
