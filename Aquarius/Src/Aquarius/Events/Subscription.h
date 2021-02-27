#pragma once

#include "Aquarius/Core/Log.h"

#include <GLFW/glfw3.h>
#include <list>


namespace Aquarius {

    class Subscription
    {
    public:
        virtual ~Subscription() = default;
        virtual void subscribe() = 0;
        virtual void unSubscribe() = 0;
        virtual void notify() = 0;
    };

    class KeyPressed : public Subscription
    {
    public:
        void subscribe() override
        {
            KeyPressedSubscribers.push_back();
        }

        void unSubscribe() override
        {
            KeyPressedSubscribers.remove();
        }

        void notify() override
        {
            std::list<int>::iterator iterator = KeyPressedSubscribers.begin();

            while(iterator != KeyPressedSubscribers.end())
            {
                // put update here
                iterator++;
            }
        }

    private:
        std::list<int> KeyPressedSubscribers;
    };

    class KeyRepeated : public Subscription
    {
    public:
        void subscribe() override
        {
            KeyRepeatedSubscribers.push_back();
        }

        void unSubscribe() override
        {
            KeyRepeatedSubscribers.remove();
        }

        void notify() override
        {
            std::list<int>::iterator iterator = KeyRepeatedSubscribers.begin();

            while(iterator != KeyRepeatedSubscribers.end())
            {
                // put update here
                iterator++;
            }
        }

    private:
        std::list<int> KeyRepeatedSubscribers;
    };

    class KeyReleased : public Subscription
    {
    public:
        void subscribe() override
        {
            KeyReleasedSubscribers.push_back();
        }

        void unSubscribe() override
        {
            KeyReleasedSubscribers.remove();
        }

        void notify() override
        {
            std::list<int>::iterator iterator = KeyReleasedSubscribers.begin();

            while(iterator != KeyReleasedSubscribers.end())
            {
                // put update here
                iterator++;
            }
        }

    private:
        std::list<int> KeyReleasedSubscribers;
    };

    class MousePressed : public Subscription
    {
    public:
        void subscribe() override
        {
            MousePressedSubscribers.push_back();
        }

        void unSubscribe() override
        {
            MousePressedSubscribers.remove();
        }

        void notify() override
        {
            std::list<int>::iterator iterator = MousePressedSubscribers.begin();

            while(iterator != MousePressedSubscribers.end())
            {
                // put update here
                iterator++;
            }
        }

    private:
        std::list<int> MousePressedSubscribers;
    };

    class MouseReleased : public Subscription
    {
    public:
        void subscribe() override
        {
            MouseReleasedSubscribers.push_back();
        }

        void unSubscribe() override
        {
            MouseReleasedSubscribers.remove();
        }

        void notify() override
        {
            std::list<int>::iterator iterator = MouseReleasedSubscribers.begin();

            while(iterator != MouseReleasedSubscribers.end())
            {
                // put update here
                iterator++;
            }
        }

    private:
        std::list<int> MouseReleasedSubscribers;
    };

    class MouseScrolled : public Subscription
    {
    public:
        void subscribe() override
        {
            MouseScrolledSubscribers.push_back();
        }

        void unSubscribe() override
        {
            MouseScrolledSubscribers.remove();
        }

        void notify() override
        {
            std::list<int>::iterator iterator = MouseScrolledSubscribers.begin();

            while(iterator != MouseScrolledSubscribers.end())
            {
                // put update here
                iterator++;
            }
        }

    private:
        std::list<int> MouseScrolledSubscribers;
    };

} // namespace Aquarius
