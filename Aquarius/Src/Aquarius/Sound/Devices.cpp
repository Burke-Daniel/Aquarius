#include "Devices.h"
#include "Aquarius/Core/Log.h"
#include <AL/alc.h>


namespace Aquarius {

    namespace Sound {

        Device::Device()
        {
            Initialize();
        }

        void Device::Initialize()
        {
            m_Device = alcOpenDevice(nullptr);

            if (!m_Device)
            {
                AQ_CORE_ERROR("Failed to open a sound device");
                return;
            }

            else
            {
                AQ_CORE_INFO("A sound device was successfully opened");
            }

            m_Context = alcCreateContext(m_Device, nullptr);

            if (!m_Context)
            {
                AQ_CORE_ERROR("Failed to create the sound context");
            }

            else
                {
                AQ_CORE_INFO("Sound context created successfully");
            }

            if (!alcMakeContextCurrent(m_Context))
            {
                AQ_CORE_ERROR("Failed to make the context current");
            }
        }

        Device * Device::get()
        {
            static Device* device = new Device();
            return device;
        }

        Device::~Device()
        {
            Deallocate();
        }

        void Device::Deallocate()
        {
            if (!alcMakeContextCurrent(nullptr))
            {
                AQ_CORE_ERROR("Failed to set context null");
            }

            alcDestroyContext(m_Context);

            if (m_Context)
            {
                AQ_CORE_ERROR("Failed to unset context while closing");
            }

            if (!alcCloseDevice(m_Device))
            {
                AQ_CORE_ERROR("Failed to close sound device");
            }
        }

    } // namespace Sound

} // namespace Aquarius
