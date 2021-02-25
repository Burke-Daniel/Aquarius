#pragma once

#include <GLFW/glfw3.h>
#include "Aquarius/Core/Log.h"

namespace Aquarius {

    class MouseEvent
    {
    public:
        static void cursorPositionCallback(GLFWwindow* window, double xPosition, double yPosition)
        {
            // TODO: Discuss if we want to only keep track of cursor position when the cursor is on
            //  the Application window, if so can combine this callback method and the one below.
            AQ_INFO("x position: %v", xPosition);
            AQ_INFO("y position: %v", yPosition);
        }

        static void cursorInWindowCallback(GLFWwindow* window, int inWindow)
        {
            if (inWindow)
            {
                AQ_INFO("Cursor has entered application window.");
            }

            else
            {
                AQ_INFO("Cursor has left application window.");
            }
        }

        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifications)
        {
            switch (action)
            {
                //TODO: Get it so mouse button name is printed rather then number, this is not critical but would be
                // nice to have.
                case GLFW_PRESS:
                    AQ_INFO("mouse button %v is pressed.", button);
                    break;

                case GLFW_RELEASE:
                    AQ_INFO("mouse button %v has been released.", button);
                    break;

                default:
                    break;
            }
        }

        static void mouseScrollCallback(GLFWwindow* window, double xOffSet, double yOffset)
        {
            AQ_INFO("x offset: %v", xOffSet);
            AQ_INFO("y offset: %v", yOffset);
        }
    };
} // namespace Aquarius
