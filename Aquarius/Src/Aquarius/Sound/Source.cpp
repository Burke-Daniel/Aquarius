#include "Source.h"
#include <AL/al.h>

#include "Aquarius/Core/Log.h"


namespace Aquarius {

    namespace Sound {

        Source::Source()
        {
            alGenSources(1, &m_Source);
            alSourcef(m_Source, AL_PITCH, m_Pitch);
            alSourcef(m_Source, AL_GAIN, m_Gain);
            alSource3f(m_Source, AL_POSITION, m_Position[0], m_Position[1], m_Position[2]);
            alSource3f(m_Source, AL_VELOCITY, m_Velocity[0], m_Velocity[1], m_Velocity[2]);
            alSourcei(m_Source, AL_LOOPING, m_Loop);
            alSourcei(m_Source, AL_BUFFER, m_Buffer);
        }

        Source::~Source()
        {
            alDeleteSources(1, &m_Source);
        }

    	void Source::beginSoundThread()
        {
            m_SoundThread = std::thread([&]()
            {
            	while (!m_SoundThreadShouldExit)
            	{
                    audioLoop();
            	}
            });
        }

    	void Source::endSoundThread()
        {
            m_SoundThreadShouldExit = true;

            m_SoundThread.join();
        }

        void Source::audioLoop()
        {
            uint32_t sound = -1;
            {
                std::lock_guard<std::mutex> lock(m_SoundMutex);
                if (!m_QueuedSounds.empty())
                {
                    sound = m_QueuedSounds.front();
                    m_QueuedSounds.pop();
                }
            }

            if (sound != -1)
            {
                playSound(sound);
            }
        }

        void Source::playSound(const uint32_t sound_buffer)
        {
            if(sound_buffer != m_Buffer)
            {
                m_Buffer = sound_buffer;
                alSourcei(m_Source, AL_BUFFER, (int32_t)m_Buffer);
            }

            alSourcePlay(m_Source);

            int32_t status = AL_PLAYING;
            AQ_CORE_TRACE("Sound is playing");

            while(status == AL_PLAYING && alGetError() == AL_NO_ERROR)
            {
                AQ_CORE_TRACE("Still playing sound");
                alGetSourcei(m_Source, AL_SOURCE_STATE, &status);
            }

        }

        void Source::queueSound(uint32_t sound_buffer)
        {
            std::lock_guard<std::mutex> lock(m_SoundMutex);
            m_QueuedSounds.push(sound_buffer);
        }

    } // namespace Sound

} // namespace Aquarius
