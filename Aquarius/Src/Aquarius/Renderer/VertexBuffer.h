#pragma once

#include <cstdint>
#include <stddef.h>

namespace Aquarius {

    class VertexBuffer
    {
    public:
        VertexBuffer(float* data, size_t size);
        VertexBuffer(double* data, size_t size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_ID;
    };

} // namespace Aquarius
