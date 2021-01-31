
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <easylogging++.h>
#include <stb_image.h>
#include <glm/glm.hpp>

#define AQ_LOG_INFO LOG(INFO)
#define AQ_LOG_WARNING LOG(WARNING)

namespace Aquarius {
    class Test
    {
    public:
        int testMain();
    };
}
