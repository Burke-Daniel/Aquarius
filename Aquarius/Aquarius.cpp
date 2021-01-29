#include "Aquarius.h"

INITIALIZE_EASYLOGGINGPP

int Aquarius::Test::testMain()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Aquarius-Test", NULL, NULL);
    if (window == NULL)
    {
        AQ_LOG_WARNING << "Could not create window";
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        AQ_LOG_WARNING << "Could not initialize glad";
        return -1;
    }

    AQ_LOG_INFO << "Window created successfully!";
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}