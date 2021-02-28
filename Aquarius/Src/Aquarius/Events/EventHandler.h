#pragma once

#include "Event.h"
#include "Aquarius/Core/Log.h"

#include <GLFW/glfw3.h>
#include <map>
#include <vector>


namespace Aquarius {

    template <typename T>
    class EventHandler
    {
    private:
        using functionType = std::function<void(const Event<T>&)>;
        std::map<T, std::vector<functionType>> subscribers;

    public:
        void subscribe(T Type, const functionType& function)
        {
            subscribers[Type].push_back(function);
        }

        void notify(Event<T>& event)
        {
            // Check to see if at end of subscribers
            if((subscribers.find(event.getEventType())) == subscribers.end())
                return;

            for(auto&& subscriber : subscribers.at(event.getEventType()))
            {
                // Notify of event only if the event has not already been handled
                if(event.handledStatus() == 0)
                {
                    subscriber(event);
                }
            }
        }
    };

} // namespace Aquarius
