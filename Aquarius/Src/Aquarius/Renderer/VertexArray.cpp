#include "VertexArray.h"

#include <glad/glad.h>


namespace Aquarius {

    VertexArray::VertexArray(sharedPtr<VertexBuffer> vertexBuffer,
                             sharedPtr<IndexBuffer> indexBuffer,
                             const BufferLayout& bufferLayout)
            : m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer)
    {
        glGenVertexArrays(1, &m_ID);
        setIndexBuffer(indexBuffer);
        setVertexBuffer(vertexBuffer, bufferLayout);
    }

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_ID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
    }

    void VertexArray::activate()
    {
        glBindVertexArray(m_ID);
    }

    void VertexArray::deactivate()
    {
        glBindVertexArray(0);
    }

    void VertexArray::setVertexBuffer(sharedPtr<VertexBuffer> vertexBuffer, const BufferLayout& bufferLayout)
    {
        activate();
        vertexBuffer->Bind();
        m_VertexBuffer = vertexBuffer;
        setBufferLayout(bufferLayout);
    }

    void VertexArray::setVertexBuffer(sharedPtr<VertexBuffer> vertexBuffer)
    {
        activate();
        vertexBuffer->Bind();
        m_VertexBuffer = vertexBuffer;
    }

    void VertexArray::setIndexBuffer(sharedPtr<IndexBuffer> indexBuffer)
    {
        activate();
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }

    void VertexArray::setBufferLayout(const BufferLayout& bufferLayout)
    {
        activate();

        uint32_t vertexAttribIndex = 0;
        for (const auto& elem : bufferLayout.getElements())
        {
            glEnableVertexAttribArray(vertexAttribIndex);
            glVertexAttribPointer(vertexAttribIndex,
                                  elem.getCount(),
                                  elem.getType(),
                                  elem.getNormalize() ? GL_TRUE : GL_FALSE,
                                  bufferLayout.getStride(),
                                  (void*)elem.getOffset());
            vertexAttribIndex++;
        }
    }

    VertexBuffer* VertexArray::getVertexBuffer() const
    {
        return m_VertexBuffer.get();
    }

    IndexBuffer* VertexArray::getIndexBuffer() const
    {
        return m_IndexBuffer.get();
    }

} // namespace Aquarius
