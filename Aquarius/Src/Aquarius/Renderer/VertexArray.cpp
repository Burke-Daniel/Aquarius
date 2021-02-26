#include "VertexArray.h"

#include <glad/glad.h>


namespace Aquarius {

    VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer,
                             const std::shared_ptr<IndexBuffer>& indexBuffer,
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

    void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& bufferLayout)
    {
        activate();
        vertexBuffer->Bind();
        m_VertexBuffer = vertexBuffer;
        setBufferLayout(bufferLayout);
    }

    void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        activate();
        vertexBuffer->Bind();
        m_VertexBuffer = vertexBuffer;
    }

    void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        activate();
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }

    void VertexArray::setBufferLayout(const BufferLayout& bufferLayout)
    {
        activate();

        uint32_t vertexAttribIndex = 0;
        for (auto elem : bufferLayout.getElements())
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

    std::shared_ptr<VertexBuffer> VertexArray::getVertexBuffer() const
    {
        return m_VertexBuffer;
    }

    std::shared_ptr<IndexBuffer> VertexArray::getIndexBuffer() const
    {
        return m_IndexBuffer;
    }

} // namespace Aquarius
