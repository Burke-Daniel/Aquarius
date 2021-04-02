/*
#include "SoundBuffer.h"
#include "Aquarius/Core/Log.h"
#include "sndfile.h"
#include <AL/alext.h>

namespace Aquarius
{

    SoundBuffer* SoundBuffer::get()
    {
        static SoundBuffer* sound_buffer = new SoundBuffer();
        return sound_buffer;
    }

    uint32_t SoundBuffer::addEffect(const char *file_name)
    {
        uint32_t error;
        uint32_t format;
        uint32_t buffer;
        SNDFILE* sound_file;
        SF_INFO sound_file_info;
        short* holding_buffer;
        int64_t number_of_frames;
        int32_t number_of_bytes;

        sound_file = sf_open(file_name, SFM_READ, &sound_file_info);

        if(!sound_file)
        {
            AQ_CORE_ERROR("Unable to open audio file %v, due to %v", file_name, sf_strerror(sound_file));
        }

        if(sound_file_info.frames < 1 || sound_file_info.frames > (int64_t)(INT_MAX / sizeof(short)) /
                sound_file_info.channels)
        {
            AQ_CORE_ERROR("There is a bad sample count in %v", file_name);
            sf_close(sound_file);
        }

        format = AL_NONE;

        switch(sound_file_info.channels)
        {
            case(1):
            {
                format = AL_FORMAT_MONO16;
                break;
            }

            case(2):
            {
                format = AL_FORMAT_STEREO16;
                break;
            }

            case(3):
            {
                if(sf_command(sound_file, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
                {
                    format = AL_FORMAT_BFORMAT2D_16;
                }

                break;
            }

            case(4):
            {
                if(sf_command(sound_file, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
                {
                   format = AL_FORMAT_BFORMAT3D_16;
                }
                break;
            }

            default:
                AQ_CORE_ERROR("Unsupported audio file format for: %v", file_name);
                sf_close(sound_file);
        }

        holding_buffer = static_cast<short*>(malloc((size_t)(sound_file_info.frames * sound_file_info.channels) * sizeof(short)));

        number_of_frames = sf_read_short(sound_file, holding_buffer, sound_file_info.frames);

        if(number_of_frames)
        {
            free(holding_buffer);
            sf_close(sound_file);
            AQ_CORE_ERROR("Failed to read samples from: %v", file_name);
        }

        number_of_bytes = (int32_t)(number_of_frames * sound_file_info.channels) * (int32_t)sizeof(short);

        buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, holding_buffer, number_of_bytes, sound_file_info.samplerate);

        free(holding_buffer);
        sf_close(sound_file);

        error = alGetError();

        if(error != AL_NO_ERROR)
        {
            AQ_CORE_ERROR("OpenAL Error: %v", alGetString(error));

            if(buffer && alIsBuffer(buffer))
            {
                alDeleteBuffers(1, &buffer);
            }
        }

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

} // namespace Aquarius */
