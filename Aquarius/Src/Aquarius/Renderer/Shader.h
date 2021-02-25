#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <unordered_map>


namespace Aquarius {

    class Shader
    {
    public:
        Shader() = delete;

        // Path to vertex and fragment shader source code
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        // Enable/disable this shader
        void activate();
        void deactivate();

        // Set uniform methods
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setInt2(const std::string& name, const glm::ivec2& values) const;
        void setInt3(const std::string& name, const glm::ivec3& values) const;
        void setInt4(const std::string& name, const glm::ivec4& values) const;
        void setFloat(const std::string& name, float value) const;
        void setFloat2(const std::string& name, const glm::vec2& values) const;
        void setFloat3(const std::string& name, const glm::vec3& values) const;
        void setFloat4(const std::string& name, const glm::vec4& values) const;
        void setMat4(const std::string& name, bool transpose, const glm::mat4& value) const;

        enum class ShaderType
        {
            VERTEX_SHADER,
            FRAGMENT_SHADER
        };

        static const std::unordered_map<ShaderType, std::string> shaderTypeToString;

    private:
        void compile(uint32_t shaderID, const char* shaderCode, ShaderType shaderType);
        void link(uint32_t vertexID, uint32_t fragmentID);
        uint32_t m_ID;
    };

} // namespace Aquarius
