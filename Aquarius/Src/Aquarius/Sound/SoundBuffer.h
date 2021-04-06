#pragma once
#include <cstdint>
#include <vector>


namespace Aquarius {

    namespace Sound {

        class SoundBuffer
        {
        public:
            static SoundBuffer* get();

            uint32_t addEffect(const std::string file_path);
            bool removeEffect(const uint32_t& data);

        private:
            SoundBuffer();
            ~SoundBuffer();
            int m_Channels;
            int m_bitsPerSample;
            std::vector<uint32_t> m_EffectBuffer;
        };

    } // namespace Sound

} // namespace Aquarius
