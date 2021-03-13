#pragma once


namespace Aquarius {

    enum class eventType
    {
        None = 0,
        KeyPressedEvent, KeyRepeatedEvent, KeyReleasedEvent,
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent, MouseInWindowEvent,
        WindowResizedEvent
    };

#define EVENT_TYPE(type) static eventType getStaticType() { return eventType::type; }\
                                                            virtual eventType getEventType() const override { return getStaticType(); }\
                                                            virtual std::string getName() const override { return #type; }

    class Event
    {
    public:
        virtual eventType getEventType() const = 0;
        virtual std::string getName() const = 0;
        virtual void logEvent() const {}
        virtual ~Event() = default;

        bool isHandled() const
        {
            return m_Handled;
        };

    private:
        bool m_Handled = false;
    };

} // namespace Aquarius
