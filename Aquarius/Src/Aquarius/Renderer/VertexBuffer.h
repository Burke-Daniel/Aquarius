#pragma once

#include <cstdint>
#include <stddef.h>

namespace Aquarius {

    class VertexBuffer
    {
    public:
        VertexBuffer(uint32_t size);
        VertexBuffer(float* data, size_t size);
        VertexBuffer(double* data, size_t size);
        ~VertexBuffer();

        void loadData(float* data, uint32_t offset, uint32_t size) const;
        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_ID;
    };

} // namespace Aquarius
