#pragma once

#include "Event.h"

#include <functional>
#include <unordered_map>
#include <vector>


namespace Aquarius {

    class EventHandler
    {
    public:
        using functionType = std::function<void(const Event&)>;

        void subscribe(eventType type, const functionType& function)
        {
            subscribers[type].push_back(function);
        }

        void notify(Event& event)
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
        std::unordered_map<eventType, std::vector<functionType>> subscribers;
    };

} // namespace Aquarius
