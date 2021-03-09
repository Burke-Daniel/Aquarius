#pragma once

#include "Aquarius/Core/Log.h"
#include "Aquarius/Events/KeyboardEvent.h"
#include "Aquarius/Events/MouseEvent.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    static void keyboardCallback(GLFWwindow *window, int key, int scanCode, int action, int modifications)
        {
            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key);
                    event.logEvent();
                    break;
                }

                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    event.logEvent();
                    break;
                }

                case GLFW_REPEAT:
                {
                    KeyRepeatedEvent event(key,1);
                    event.logEvent();
                    break;
                }

                default:
                    break;
            }
        }

        static void mouseCursorPositionCallback(GLFWwindow *window, double xPosition, double yPosition)
        {
            MouseMovedEvent event(xPosition, yPosition);
            event.logEvent();
        }

        static void mouseCursorInWindowCallback(GLFWwindow *window, int inWindow)
        {
            MouseInWindowEvent event(inWindow);
            event.logEvent();
        }

        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int modifications)
        {
            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    event.logEvent();
                    break;
                }

                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    event.logEvent();
                    break;
                }

                default:
                    break;
            }
        }

        static void mouseScrollCallback(GLFWwindow *window, double xOffSet, double yOffset)
        {
            MouseScrolledEvent event(xOffSet, yOffset);
            event.logEvent();
        }

} // namespace Aquarius
