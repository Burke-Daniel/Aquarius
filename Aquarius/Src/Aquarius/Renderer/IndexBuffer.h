#pragma once

#include <cstdint>
#include <stddef.h>


namespace Aquarius {

    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* data, size_t count);
        IndexBuffer(uint16_t* data, size_t count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        size_t getCount();

    private:
        uint32_t m_ID;
        size_t m_Count;
    };

} // namespace Aquarius
