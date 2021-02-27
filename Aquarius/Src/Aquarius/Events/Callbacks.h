#pragma once

#include "Aquarius/Core/Log.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    class KeyboardEvent
    {
    public:
        static void Callback(GLFWwindow* window, int key, int scanCode, int action, int modifications)
        {
            switch (action)
            {
                case GLFW_PRESS:
                    AQ_INFO("key %v is pressed.", key);
                    break;

                case GLFW_RELEASE:
                    AQ_INFO("key %v has been released.", key);
                    break;

                case GLFW_REPEAT:
                    AQ_INFO("key %v is being pressed repeatedly.", key);
                    break;

                default:
                    break;
            }
        }
    };

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

    class WindowEvent
    {
    public:

        static void windowCloseCallback(GLFWwindow* window)
        {
            //TODO Implement
        }

        static void windowSizeCallback(GLFWwindow* window, int width, int height)
        {
            //TODO Implement
        }

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            //TODO Implement
        }

        static void windowContentScaleCallBack(GLFWwindow* window, float xscale, float yscale)
        {
            //TODO Implement
        }

        static void windowPositionChangedCallback(GLFWwindow* window, int xposition, int yposition)
        {
            //TODO Implement
        }

        static void windowIconifyCallBack(GLFWwindow* window, int iconified)
        {
            //TODO Implement
        }

        static void windowMaximizedCallBack(GLFWwindow* window, int maximized)
        {
            //TODO Implement
        }

        static void windowFocusedCallBack(GLFWwindow*, int focused)
        {
            //TODO Implement
        }

        static void windowRefreshRequiredCallback(GLFWwindow*)
        {
            //TODO Implement
        }
    };

} // namespace Aquarius
