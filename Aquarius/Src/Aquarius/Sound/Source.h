#pragma once
#include <cstdint>

#include <future>
#include <mutex>
#include <queue>


namespace Aquarius {

    namespace Sound {

        class Source
        {
        public:
            Source();
            ~Source();

            void audioLoop(bool* soundThreadShouldStop);
            void queueSound(uint32_t sound_buffer);

            std::mutex m_SoundMutex;

        private:

            void playSound(const uint32_t sound_buffer);
            
            float m_Position[3] = {0,0,0};
            float m_Velocity[3] = {0,0,0};
            uint32_t m_Source;
            float m_Gain = 1.f;
            float m_Pitch = 1.f;
            bool m_Loop = false;
            uint32_t m_Buffer = 0;
            std::queue<uint32_t> m_QueuedSounds;
        };

    } // namespace Sound

} // namespace Aquarius
