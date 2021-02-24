#pragma once
#include <cstdint>

namespace Aquarius {

    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* data, size_t count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        size_t getCount();

    private:
        uint32_t m_ID;
        size_t m_Count;
    };
}
