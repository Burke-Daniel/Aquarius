#pragma once
#include <cstdint>
#include <vector>
#include <string>


namespace Aquarius {

    namespace Sound {

        class SoundBuffer
        {
        public:
            static SoundBuffer* get();

            uint32_t addEffect(const std::string file_path);

        private:
            SoundBuffer();
            ~SoundBuffer();
            std::vector<uint32_t> m_EffectBuffer;
        };

    } // namespace Sound

} // namespace Aquarius
