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

            void beginSoundThread();
            void endSoundThread();
            void queueSound(uint32_t sound_buffer);

        private:
            void audioLoop();
            void playSound(const uint32_t sound_buffer);

        	// OpenAL Related stuff
            float m_Position[3] = {0,0,0};
            float m_Velocity[3] = {0,0,0};
            uint32_t m_Source;
            float m_Gain = 1.f;
            float m_Pitch = 1.f;
            bool m_Loop = false;
            uint32_t m_Buffer = 0;

        	// Thread management
            std::queue<uint32_t> m_QueuedSounds;
            std::mutex m_SoundMutex;
            std::thread m_SoundThread;
            std::atomic_bool m_SoundThreadShouldExit = { false };
        };

    } // namespace Sound

} // namespace Aquarius
