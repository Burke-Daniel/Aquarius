#include "Devices.h"
#include "Aquarius/Core/Log.h"
#define AL_LIBTYPE_STATIC
#include <AL/alc.h>


namespace Aquarius {

    Device::Device()
    {
        m_Device = alcOpenDevice(nullptr);

        if (!m_Device)
        {
            AQ_CORE_ERROR("Failed to open a sound device");
        }

        else
            {
            AQ_CORE_INFO("A sound device was successfully opened");
        }

        m_Context = alcCreateContext(m_Device, nullptr);

        if (!m_Context) {
            AQ_CORE_ERROR("Failed to create the sound context");
        } else {
            AQ_CORE_INFO("Sound context created successfully");
        }

        if (!alcMakeContextCurrent(m_Context))
        {
            AQ_CORE_ERROR("Failed to make the context current");
        }
    }

    uniquePtr<Device> Device::Create()
    {
        return std::make_unique<Device>();
    }

    Device::~Device()
    {
        if(!alcMakeContextCurrent(nullptr))
        {
            AQ_CORE_ERROR("Failed to set context null");
        }

        alcDestroyContext(m_Context);

        if(m_Context)
        {
            AQ_CORE_ERROR("Failed to unset context while closing");
        }

        if(!alcCloseDevice(m_Device))
        {
            AQ_CORE_ERROR("Failed to close sound device");
        }
    }

} // namespace Aquarius
