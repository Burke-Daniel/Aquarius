#pragma once

#include "Aquarius/Core/Log.h"
#include "Aquarius/Core/Input.h"
#include "Event.h"

#include <GLFW/glfw3.h>

namespace Aquarius {

    class Keyboard : public Event
    {
    public:
        KeyCode GetKeyCode() const
        {
            return m_KeyCode;
        }
    protected:
        KeyCode(const KeyCode keycode)
            : m_KeyCode(keycode) {}

            KeyCode m_KeyCode;
    };

    class KeyPressed : public Keyboard
    {
    public:
        KeyPressed(const KeyCode keycode, const unit16_t repeatCount)
            : Keyboard(keycode), m_RepeatCount(repeatCount) {}

        unit16_t GetRepeatCount() const
        {
            return m_RepeatCount;
        }

        AQ_CORE_INFO("KeyPressedEvent: %v", m_KeyCode);

        if (GetRepeatCount == 0)
        {
            EVENT_TYPE(InputEvent | KeyboardEvent | KeyPressedEvent)
        }

        else
        {
            //EVENT_TYPE(Input)
        }


        AQ_CORE_INFO("Number of repetitions of KeyPressedEvent: %v", m_RepeatCount);
    private:
        unit16_t m_RepeatCount;
    };

    class KeyReleased : public Keyboard
    {
    public:
        KeyReleased(const KeyCode keycode)
                : Keyboard(keycode) {}

        EVENT_TYPE(InputEvent | KeyboardEvent | KeyReleasedEvent)
        AQ_CORE_INFO("KeyPressedEvent: %v", m_KeyCode);
        AQ_CORE_INFO("Number of repetitions of KeyPressedEvent: %v", m_RepeatCount);
    private:
        unit16_t m_RepeatCount;
    };





} // namespace Aquarius
