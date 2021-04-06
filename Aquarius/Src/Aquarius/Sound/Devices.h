#pragma once

#include <AL/alc.h>
#include <memory>


namespace Aquarius {

    namespace Sound {
        class Device
        {
        public:
            static Device* get();

        private:
            Device();
            ~Device();
            void Initialize();
            void Deallocate();
            ALCdevice* m_Device;
            ALCcontext* m_Context;
        };

    } // namespace Sound

} // namespace Aquarius
