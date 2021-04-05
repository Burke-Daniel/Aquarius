#pragma once

#include "Aquarius/Events/Event.h"
#include "Aquarius/Core/Log.h"


namespace Aquarius {

    class WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(int width, int height) : m_Width(width), m_Height(height) {}

        EVENT_TYPE(WindowResizedEvent)

        void logEvent() const override
        {
            AQ_CORE_TRACE("WindowResizedEvent %v, %v", m_Width, m_Height);
        }

        int getWidth() const
        {
            return m_Width;
        }

        int getHeight() const
        {
            return m_Height;
        }

    private:
        int m_Width;
        int m_Height;
    };

} // namespace Aquarius
