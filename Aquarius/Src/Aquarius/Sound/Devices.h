#pragma once

#include "Aquarius/Core/Utility.h"
#define AL_LIBTYPE_STATIC
#include <AL/alc.h>
#include <memory>


namespace Aquarius {

    class Device
    {
    public:
        // Creation
        Device();
        static uniquePtr<Device> Create();

        // Destruction
        ~Device();
    private:
        ALCdevice* m_Device;
        ALCcontext* m_Context;
    };

} // namespace Aquarius
