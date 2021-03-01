#pragma once

#include "Aquarius/Core/Log.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    static void keyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int modifications)
    {
        switch (action)
            {
                case GLFW_PRESS:
                    AQ_CORE_TRACE("key %v is pressed.", key);
                    break;

                case GLFW_RELEASE:
                    AQ_CORE_TRACE("key %v has been released.", key);
                    break;

                case GLFW_REPEAT:
                    AQ_CORE_TRACE("key %v is being pressed repeatedly.", key);
                    break;

                default:
                    break;
            }
    }

    static void mouseCursorPositionCallback(GLFWwindow* window, double xPosition, double yPosition)
    {
            AQ_CORE_TRACE("x position: %v", xPosition);
            AQ_CORE_TRACE("y position: %v", yPosition);
    }

    static void mouseCursorInWindowCallback(GLFWwindow* window, int inWindow)
    {
        if (inWindow)
        {
            AQ_CORE_TRACE("Cursor has entered application window.");
        }

        else
            {
                AQ_CORE_TRACE("Cursor has left application window.");
            }
    }

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifications)
    {
        switch (action)
            {
                case GLFW_PRESS:
                    AQ_CORE_TRACE("mouse button %v is pressed.", button);
                    break;

                case GLFW_RELEASE:
                    AQ_CORE_TRACE("mouse button %v has been released.", button);
                    break;

                default:
                    break;
            }
    }

    static void mouseScrollCallback(GLFWwindow* window, double xOffSet, double yOffset)
    {
        AQ_CORE_TRACE("x offset: %v", xOffSet);
        AQ_CORE_TRACE("y offset: %v", yOffset);
    }

} // namespace Aquarius
