#pragma once

#include <GLFW/glfw3.h>
#include "Aquarius/Core/Log.h"

namespace Aquarius {
    class KeyboardEvent {
    public:
        static void Callback(GLFWwindow* window, int key, int scanCode, int action, int modifications)
        {
            //TODO: Get it so key button name is printed rather then number, this is not critical but would be
            // nice to have.
            switch (action)
            {
                case GLFW_PRESS:
                    AQ_INFO("key %v is pressed.", key);
                    break;

                case GLFW_RELEASE:
                    AQ_INFO("key %v has been released.", key);
                    break;

                case GLFW_REPEAT:
                    AQ_INFO("key %v is being pressed repeatedly. ", key);
                    break;

                default:
                    break;
            }
        }
    };
}
