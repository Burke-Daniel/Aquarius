#pragma once

#include "Aquarius/Core/Application.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Events/KeyboardEvent.h"
#include "Aquarius/Events/MouseEvent.h"
#include "Aquarius/Events/WindowEvent.h"

#include <GLFW/glfw3.h>


namespace Aquarius {

    namespace Callbacks {
        static void keyboardCallback(GLFWwindow *window, int key, int scanCode, int action, int modifications)
        {
            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key);
                    event.logEvent();
                    Application::get()->onEvent(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    event.logEvent();
                    Application::get()->onEvent(event);
                    break;
                }

                case GLFW_REPEAT:
                {
                    KeyRepeatedEvent event(key,1);
                    event.logEvent();
                    Application::get()->onEvent(event);
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
            Application::get()->onEvent(event);
        }

        static void mouseCursorInWindowCallback(GLFWwindow *window, int inWindow)
        {
            MouseInWindowEvent event(inWindow);
            event.logEvent();
            Application::get()->onEvent(event);
        }

        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int modifications)
        {
            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    event.logEvent();
                    Application::get()->onEvent(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    event.logEvent();
                    Application::get()->onEvent(event);
                    break;
                }

                default:
                    break;
            }
        }

        static void mouseScrollCallback(GLFWwindow *window, double xOffSet, double yOffset)
        {
            MouseScrolledEvent event(xOffset, yOffset);
            event.logEvent();
            Application::get()->onEvent(event);
        }

        static void windowResizeCallback(GLFWwindow *window, int width, int height)
        {
            WindowResizedEvent event(width, height);
            event.logEvent();
            Application::get()->onEvent(event);
        }

    } // namespace Callbacks

} // namespace Aquarius
