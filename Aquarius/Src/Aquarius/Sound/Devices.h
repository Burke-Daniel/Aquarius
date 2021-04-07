#pragma once

#include <AL/alc.h>
#include <memory>


namespace Aquarius {

    namespace Sound {

        class Device
        {
        public:
            static Device* get();
            void Deallocate();

            ~Device();

            Device();

        private:
            void Initialize();
            static Device* device;
            ALCdevice* m_Device;
            ALCcontext* m_Context;
        };

    } // namespace Sound

} // namespace Aquarius
