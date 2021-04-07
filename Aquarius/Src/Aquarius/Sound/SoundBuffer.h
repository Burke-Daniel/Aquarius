#pragma once

#include "Aquarius/Core/Utility.h"

#include <cstdint>
#include <vector>
#include <string>
#include <memory>


namespace Aquarius {

    namespace Sound {

        class SoundBuffer
        {
        public:
            SoundBuffer();
            static uniquePtr<SoundBuffer> Create();

            uint32_t addEffect(const std::string file_path);

        private:
            std::vector<uint32_t> m_EffectBuffer;
        };

    } // namespace Sound

} // namespace Aquarius
