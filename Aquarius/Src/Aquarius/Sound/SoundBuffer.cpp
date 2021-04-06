#include "SoundBuffer.h"
#include "Aquarius/Core/Log.h"
#include <AudioFile.h>
#include <AL/alext.h>
#include <AL/al.h>


namespace Aquarius {

    namespace Sound {

        SoundBuffer* SoundBuffer::get()
        {
            static SoundBuffer* sound_buffer = new SoundBuffer();
            return sound_buffer;
        }

        uint32_t SoundBuffer::addEffect(const std::string file_path)
        {
            uint32_t buffer = 0;
            alGenBuffers(1, &buffer);

            uint32_t format;

            AudioFile<float> sound_file;

            bool loaded = sound_file.load(file_path);

            if(!loaded)
            {
                AQ_CORE_ERROR("Unable to open audio file %v, due to %v", file_path);
            }

            m_Channels = sound_file.getNumChannels();
            m_bitsPerSample = sound_file.getBitDepth();

            //Determine WAV format
            if (m_Channels == 1 && m_bitsPerSample == 8)
            {
                format = AL_FORMAT_MONO8;
            }

            else if (m_Channels == 1 && m_bitsPerSample == 16)
            {
                format = AL_FORMAT_MONO16;
            }

            else if (m_Channels == 1 && m_bitsPerSample == 8)
            {
                format = AL_FORMAT_STEREO8;
            }

            else if (m_Channels == 2 && m_bitsPerSample == 16)
            {
                format = AL_FORMAT_STEREO16;
            }

            else
            {
                AQ_CORE_ERROR("Unsupported wave format for: %v", file_path);
            }

            std::vector<uint8_t> pcmData;
            sound_file.savePCMToBuffer(pcmData);

            alBufferData(buffer, format,reinterpret_cast<ALvoid*>(pcmData.data()), pcmData.size(), sound_file.getSampleRate());

            m_EffectBuffer.push_back(buffer);

            return buffer;
        }

        bool SoundBuffer::removeEffect(const uint32_t &data)
        {
            auto iterator = m_EffectBuffer.begin();

            while (iterator != m_EffectBuffer.end())
            {
                if (*iterator == data)
                {
                    alDeleteBuffers(1, &*iterator);

                    iterator = m_EffectBuffer.erase(iterator);
                }

                else
                {
                    iterator++;
                }
            }
        }

        SoundBuffer::SoundBuffer()
        {
            m_EffectBuffer.clear();
        }

        SoundBuffer::~SoundBuffer()
        {
            alDeleteBuffers(m_EffectBuffer.size(), m_EffectBuffer.data());

            m_EffectBuffer.clear();
        }

    } // namespace Sound

} // namespace Aquarius
