/*
#pragma once
#include <cstdint>
#include <vector>


namespace Aquarius {

    class SoundBuffer
    {
    public:
        SoundBuffer();
        ~SoundBuffer();
        static SoundBuffer* get();
        uint32_t addEffect(const char *file_name);
        bool removeEffect(const uint32_t& data);
    private:
        std::vector<uint32_t> m_EffectBuffer;
    };

} // namespace Aquarius */
