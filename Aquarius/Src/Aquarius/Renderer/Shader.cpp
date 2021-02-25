#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Aquarius/Core/Log.h"



namespace Aquarius {

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        // Load shader source into string from file
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vertexFile;
        std::ifstream fragmentFile;

        // Allow the ifstream objects to throw exception on read/write error
        vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // Open shader files
            vertexFile.open(vertexPath);
            fragmentFile.open(fragmentPath);

            // Read file buffer contents
            std::stringstream vertexStream, fragmentStream;
            vertexStream << vertexFile.rdbuf();
            fragmentStream << fragmentFile.rdbuf();

            // Close files
            vertexFile.close();
            fragmentFile.close();

            vertexCode = vertexStream.str();
            fragmentCode = fragmentStream.str();
        }
        catch (std::ifstream::failure error)
        {
            AQ_CORE_ERROR("Failed to open shader file(s)\n VertexPath: %v \n FragmentPath %v",
                          vertexPath, fragmentPath);
            AQ_CORE_ERROR("Error: %v", error.what());
        }

        uint32_t vertexID;
        uint32_t fragmentID;
        vertexID = glCreateShader(GL_VERTEX_SHADER);
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

        compile(vertexID, vertexCode.c_str(), ShaderType::VERTEX_SHADER);
        compile(fragmentID, fragmentCode.c_str(), ShaderType::FRAGMENT_SHADER);
        link(vertexID, fragmentID);

        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);
    }

    Shader::~Shader()
    {
        deactivate();
        glDeleteProgram(m_ID);
    }

    void Shader::activate()
    {
        glUseProgram(m_ID);
    }

    void Shader::deactivate()
    {
        glUseProgram(0);
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform1i(location, (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform1i(location, value);
    }

    void Shader::setInt2(const std::string& name, const glm::ivec2& values) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform2i(location, values.x, values.y);
    }

    void Shader::setInt3(const std::string& name, const glm::ivec3& values) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform3i(location, values.x, values.y, values.z);
    }

    void Shader::setInt4(const std::string& name, const glm::ivec4& values) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform4i(location, values.x, values.y, values.z, values.w);
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform1f(location, value);
    }

    void Shader::setFloat2(const std::string& name, const glm::vec2& values) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform2f(location, values.x, values.y);
    }

    void Shader::setFloat3(const std::string& name, const glm::vec3& values) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform3f(location, values.x, values.y, values.z);
    }

    void Shader::setFloat4(const std::string& name, const glm::vec4& values) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniform4i(location, values.x, values.y, values.z, values.w);
    }

    void Shader::setMat4(const std::string& name, bool transpose, const glm::mat4& value) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value));
    }

    void Shader::compile(uint32_t shaderID, const char* shaderCode, ShaderType shaderType)
    {
        // Add shader source
        glShaderSource(shaderID, 1, &shaderCode, NULL);
        glCompileShader(shaderID);

        // Check for shader compile errors
        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            char compileLog[512];
            glGetShaderInfoLog(shaderID, 512, NULL, compileLog);
            AQ_CORE_ERROR("Error compiling shader of type:  %v", shaderTypeToString[shaderType]);
            AQ_CORE_ERROR("Compiler Status Message: %v", compileLog);
        }
    }

    void Shader::link(uint32_t vertexID, uint32_t fragmentID)
    {
        // Link
        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexID);
        glAttachShader(m_ID, fragmentID);
        glLinkProgram(m_ID);

        // Check for and print linking errors
        int linkSuccess;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &linkSuccess);

        if (!linkSuccess)
        {
            char linkLog[512];
            glGetProgramInfoLog(m_ID, 512, NULL, linkLog);
            AQ_CORE_ERROR("Error linking shader");
            AQ_CORE_ERROR("Linking error: %v", linkLog);
        }
    }
} // namespace Aquarius