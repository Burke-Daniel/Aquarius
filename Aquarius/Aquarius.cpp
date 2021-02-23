#define AQ_ASSERT_ENABLE

#include "Aquarius.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Core/Window.h"
#include "Aquarius/Core/Assert.h"


namespace Aquarius {

    int Test::testMain()
    {
        Log::initLoggers();

        std::unique_ptr<Window> Window = Window::Create(800, 600, "Aquarius");
        Window->Initialize();

        AQ_INFO("Testing %v %v", "client", "logger");
        AQ_CORE_INFO("Testing %v %v", "core", "logger");

        while (1)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            Window->OnUpdate();
        }

        return 0;
    }

} // namespace Aquarius

