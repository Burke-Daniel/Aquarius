#pragma once

#include <GLFW/glfw3.h>


namespace Aquarius {

    template <typename T>
    class Event
    {
    public:
        Event() = default;
        Event(T Type, const int& code, const double& xAxis, const double& yAxis) : m_Type(Type), m_Code(code),
            m_xAxis(xAxis), m_yAxis(yAxis)  {};
        virtual ~Event() = default;

        inline const T getEventType() const
        {
            return m_Type;
        }

        bool isHandled()
        {
            return m_Handled;
        }

        int getCode()
        {
            return m_Code;
        }

        double getXAxis()
        {
            return m_xAxis;
        }

        double getYAxis()
        {
            return m_yAxis;
        }

    protected:
        T m_Type;
        bool m_Handled = false;

        // The below are parameters that are used to provide more information about the event.
        // If the parameter is not applicable to the event it will be set to 0.
        // Code is used for Mouse codes & Key codes.
        int m_Code;
        double m_xAxis;
        double m_yAxis;
    };

} // namespace Aquarius
