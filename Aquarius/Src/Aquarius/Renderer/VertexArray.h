#pragma once

#include "Aquarius/Renderer/VertexBuffer.h"
#include "Aquarius/Renderer/IndexBuffer.h"

#include <cstdint>
#include <glad/glad.h>
#include <memory>
#include <unordered_map>
#include <vector>


namespace Aquarius {

    enum class ShaderType
    {
        Int,
        UInt,
        Float,
        Double,
    };

    static const std::unordered_map<ShaderType, GLenum> ShaderTypeToGLEnum =
    {
        {ShaderType::Int, GL_INT},
        {ShaderType::UInt, GL_UNSIGNED_INT},
        {ShaderType::Float, GL_FLOAT},
        {ShaderType::Double, GL_DOUBLE}
    };

    static const std::unordered_map<ShaderType, size_t>  ShaderTypeSizeBytes =
    {
            {ShaderType::Int, 4},
            {ShaderType::UInt, 4},
            {ShaderType::Float, 4},
            {ShaderType::Double, 8}
    };

    class VertexElement
    {
    public:
        VertexElement(ShaderType shaderType, size_t count, bool normalize)
        {
            m_Type = ShaderTypeToGLEnum.at(shaderType);
            m_Count = count;
            m_Normalize = normalize;
            m_Size = ShaderTypeSizeBytes.at(shaderType) * m_Count;
            m_Offset = 0;
        }

        void setOffset(size_t offset) { m_Offset = offset; }

        size_t getOffset() const { return m_Offset; }
        size_t getCount() const { return m_Count; }
        size_t getSize() const { return m_Size; }
        bool getNormalize() const { return m_Normalize; }
        GLenum getType() const { return m_Type; }

    private:
        GLenum m_Type;
        size_t m_Count;
        size_t m_Size;
        size_t m_Offset;
        bool m_Normalize;
    };


    class BufferLayout
    {
    public:
        BufferLayout(std::initializer_list<VertexElement> vertexElements)
        {
            // Calculate offset for each element
            size_t Offset = 0;
            for (auto elem : vertexElements)
            {
                elem.setOffset(Offset);
                m_Elements.push_back(elem);
                Offset += elem.getSize();
            }

            m_Stride = Offset;
        }

        const std::vector<VertexElement>& getElements() const { return m_Elements; }
        size_t getStride() const { return m_Stride; }
    private:
        std::vector<VertexElement> m_Elements;
        size_t m_Stride;
    };

    class VertexArray
    {
    public:
        VertexArray();
        VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer,
                    const std::shared_ptr<IndexBuffer>& IndexBuffer,
                    const BufferLayout& bufferLayout);
        ~VertexArray();

        void activate();
        void deactivate();
        void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer);
        void setBufferLayout(const BufferLayout& bufferLayout);

        std::shared_ptr<VertexBuffer> getVertexBuffer() const;
        std::shared_ptr<IndexBuffer> getIndexBuffer() const;

    private:
        uint32_t m_ID;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };



} // namespace Aquarius
