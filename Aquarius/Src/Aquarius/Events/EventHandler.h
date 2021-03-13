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
            m_Subscribers[type].push_back(function);
        }

        void notify(Event& event)
        {
            // Check to see if there are any subscribers of event type
            if((m_Subscribers.find(event.getEventType())) == m_Subscribers.end())
                return;

            for(auto&& subscriber : m_Subscribers.at(event.getEventType()))
            {
                // Notify of event only if the event has not already been handled
                if(!event.isHandled())
                {
                    subscriber(event);
                }

                else
                {
                    break;
                }

            }
        }

    private:
        std::unordered_map<eventType, std::vector<functionType>> m_Subscribers;
    };

} // namespace Aquarius
