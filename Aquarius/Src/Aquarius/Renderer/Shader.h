#pragma once
#include <iostream>
#include <glm/glm.hpp>

namespace Aquarius {

    enum class ShaderType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };
    std::ostream& operator<< (std::ostream& os, ShaderType shaderType);


    class Shader
    {
    public:
        Shader(const std::string& vertexPath );
        ~Shader();

        // Enable/disable this shader
        void activate();
        void deactivate();

        // Set uniform methods
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;


    private:
        void compile(uint32_t shaderID, const char* shaderCode, ShaderType shaderType);
        uint32_t m_ID;
    };

} // namespace Aquarius




