// -- Core
#include "Aquarius/Core/Utility.h"
#include "Aquarius/Core/Application.h"
#include "Aquarius/Core/Assert.h"
#include "Aquarius/Core/Input.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Core/Window.h"

// -- Renderer
#include "Aquarius/Renderer/IndexBuffer.h"
#include "Aquarius/Renderer/VertexBuffer.h"

// -- Events
#include "Aquarius/Events/Keyboard.h"
#include "Aquarius/Events/Mouse.h"
#include "Aquarius/Events/Window.h"

#include <easylogging++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stb_image.h>


namespace Aquarius {
    class Test
    {
    public:
        int testMain();
        static int triangleTest();
    };
}
