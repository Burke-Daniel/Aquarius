// Fix for std::numeric_limits on Windows, necessary to use AudioFile.h
#define NOMINMAX

#include "SoundBuffer.h"
#include "Aquarius/Core/Log.h"
#include <AudioFile.h>
#include <AL/alext.h>
#include <AL/al.h>


namespace Aquarius {

    namespace Sound {

        SoundBuffer::SoundBuffer() {}

        uniquePtr<SoundBuffer> SoundBuffer::Create()
        {
            return std::make_unique<SoundBuffer>();
        }

        SoundBuffer::~SoundBuffer()
        {
            alDeleteBuffers(m_EffectBuffer.size(), m_EffectBuffer.data());
            m_EffectBuffer.clear();
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
                return 0;
            }

            int m_Channels = sound_file.getNumChannels();
            int m_bitsPerSample = sound_file.getBitDepth();

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

    } // namespace Sound

} // namespace Aquarius
