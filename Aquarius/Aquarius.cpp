#include "Aquarius.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Events/Keyboard.h"
#include "Aquarius/Events/Mouse.h"
#include "Aquarius/Events/Window.h"

namespace Aquarius {

int Test::testMain()
{
    Log::initLoggers();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Aquarius-Test", NULL, NULL);
    if (window == NULL)
    {
        AQ_WARNING("Could not create window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        AQ_WARNING("Could not initialize glad");
        return -1;
    }

    AQ_INFO("Window created successfully!");

    //TODO Bring in neccesary set methods for window events.
    glfwSetKeyCallback(window, KeyboardEvent::Callback);
    glfwSetCursorPosCallback(window, MouseEvent::cursorPositionCallback);
    glfwSetCursorEnterCallback(window, MouseEvent::cursorInWindowCallback);
    glfwSetMouseButtonCallback(window, MouseEvent::mouseButtonCallback);
    glfwSetScrollCallback(window, MouseEvent::mouseScrollCallback);

    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetInputMode(window, GLFW_STICKY_KEYS,1);

    AQ_INFO("Testing %v %v", "client", "logger");
    AQ_CORE_INFO("Testing %v %v", "core", "logger");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

} // namespace Aquarius
