#pragma once

#include "Aquarius/Core/Log.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    template <typename T>
    class Event
    {
    public:
        Event() = default;
        Event(T Type) : type(Type) {};
        virtual ~Event() = default;

        inline const T getEventType() const
        {
            return type;
        }

        virtual bool handledStatus()
        {
            return isHandled;
        }

    protected:
        T type;
        bool isHandled = false;
    };

} // namespace Aquarius
