#pragma once

#include <GLFW/glfw3.h>
#include "Aquarius/Core/Log.h"

namespace Aquarius {

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
