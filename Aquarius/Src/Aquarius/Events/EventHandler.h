#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>


namespace Aquarius {

    template <typename T>
    class EventHandler
    {
    public:
        using functionType = std::function<void(const Event<T>&)>;
        void subscribe(T Type, const functionType& function)
        {
            subscribers[Type].push_back(function);
        }

        void notify(Event<T>& event)
        {
            // Check to see if there are any subscribers of event type
            if((subscribers.find(event.getEventType())) == subscribers.end())
                return;

            for(auto&& subscriber : subscribers.at(event.getEventType()))
            {
                // Notify of event only if the event has not already been handled
                if(!event.isHandled())
                {
                    subscriber(event);
                }
            }
        }

    private:
        std::unordered_map<T, std::vector<functionType>> subscribers;
    };

} // namespace Aquarius
