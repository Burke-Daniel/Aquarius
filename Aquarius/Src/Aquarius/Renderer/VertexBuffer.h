#pragma once
#include <cstdint>

namespace Aquarius {

    class VertexBuffer
    {
    public:
        VertexBuffer(void* data, size_t size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_ID;
    };
} // namespace Aquarius
