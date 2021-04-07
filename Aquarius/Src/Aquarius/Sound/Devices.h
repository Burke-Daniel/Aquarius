#pragma once

#include "Aquarius/Core/Utility.h"

#include <AL/alc.h>
#include <memory>


namespace Aquarius {

    namespace Sound {

        class Device
        {
        public:
            Device();
            static uniquePtr<Device> Create();
            void Deallocate();

        private:
            void Initialize();
            ALCdevice* m_Device;
            ALCcontext* m_Context;
        };

    } // namespace Sound

} // namespace Aquarius
