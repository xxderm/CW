#include "Shader.h"

Shader::Shader()
{
   
}

const unsigned Shader::getId(const char* shaderName)
{
    if (mShader.count(shaderName) > 0)
        return mShader.at(shaderName);
    LOG(ERROR) << "Shader not found";
    throw std::exception();
}

void Shader::AddShader(const char* shaderName, const char* vertexPath, const char* fragmentPath, const char* tcPath, const char* tePath, const char* geometryPath)
{
    int id;
    std::string vertexCode;
    std::string fragmentCode;
    std::string tcCode;
    std::string teCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream tcShaderFile;
    std::ifstream teShaderFile;
    std::ifstream gShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    tcShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    teShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        if (tcPath != nullptr)
        {
            tcShaderFile.open(tcPath);
            std::stringstream tcShaderStream;
            tcShaderStream << tcShaderFile.rdbuf();
            tcShaderFile.close();
            tcCode = tcShaderStream.str();
        }
        if (tePath != nullptr)
        {
            teShaderFile.open(tePath);
            std::stringstream teShaderStream;
            teShaderStream << teShaderFile.rdbuf();
            teShaderFile.close();
            teCode = teShaderStream.str();
        }
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure e)
    {
        LOG(ERROR) << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;
    (void)success;
    char infoLog[512];
    (void)infoLog;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    unsigned int tessellationControl;
    if (tcPath != nullptr)
    {
        const char* tcShaderCode = tcCode.c_str();
        tessellationControl = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tessellationControl, 1, &tcShaderCode, NULL);
        glCompileShader(tessellationControl);
        checkCompileErrors(tessellationControl, "TESSELLATION CONTROL");
    }
    unsigned int tessellationEval;
    if (tePath != nullptr)
    {
        const char* teShaderCode = teCode.c_str();
        tessellationEval = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tessellationEval, 1, &teShaderCode, NULL);
        glCompileShader(tessellationEval);
        checkCompileErrors(tessellationEval, "TESSELLATION EVAL");
    }
    unsigned int geometry;
    if (geometryPath != nullptr)
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    if (tcPath != nullptr)
        glAttachShader(id, tessellationControl);
    if (tePath != nullptr)
        glAttachShader(id, tessellationEval);
    if (geometryPath != nullptr)
        glAttachShader(id, geometry);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (tcPath != nullptr)
        glDeleteShader(tessellationControl);
    if (tePath != nullptr)
        glDeleteShader(tessellationEval);
    if (geometryPath != nullptr)
        glDeleteShader(geometry);

    mShader.try_emplace(shaderName, id);
}

void Shader::PushShader(std::string Name, bool tessShaders)
{
    if(tessShaders)
        this->AddShader(
            Name.c_str(),
            std::string("Shaders/" + Name + "Vertex.glsl").c_str(),
            std::string("Shaders/" + Name + "Fragment.glsl").c_str(),
            std::string("Shaders/" + Name + "TessControl.glsl").c_str(),
            std::string("Shaders/" + Name + "TessEval.glsl").c_str()
        );
    else
        this->AddShader(
            Name.c_str(),
            std::string("Shaders/" + Name + "Vertex.glsl").c_str(),
            std::string("Shaders/" + Name + "Fragment.glsl").c_str()
        );
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            LOG(ERROR) << "ERROR::SHADER_COMPILATION_ERROR of type: ";
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            LOG(ERROR) << "ERROR::PROGRAM_LINKING_ERROR of type: ";
        }
    }
}

void Shader::Bind(const char* shaderName)
{
    glUseProgram(getId(shaderName));
}

void Shader::UnBind(const char* shaderName)
{
    glUseProgram(0);
}

void Shader::setBool(const char* shaderName, const std::string& name, bool value) const
{
   glUniform1i(glGetUniformLocation(mShader.at(shaderName), name.c_str()), (int)value);
}

void Shader::setInt(const char* shaderName, const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(mShader.at(shaderName), name.c_str()), value);
}

void Shader::setFloat(const char* shaderName, const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(mShader.at(shaderName), name.c_str()), value);
}

void Shader::setVec2(const char* shaderName, const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(mShader.at(shaderName), name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const char* shaderName, const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(mShader.at(shaderName), name.c_str()), x, y);
}

void Shader::setVec3(const char* shaderName, const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(mShader.at(shaderName), name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const char* shaderName, const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(mShader.at(shaderName), name.c_str()), x, y, z);
}

void Shader::setVec4(const char* shaderName, const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(mShader.at(shaderName), name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const char* shaderName, const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(mShader.at(shaderName), name.c_str()), x, y, z, w);
}

void Shader::setMat2(const char* shaderName, const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(mShader.at(shaderName), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const char* shaderName, const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(mShader.at(shaderName), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const char* shaderName, const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(mShader.at(shaderName), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}