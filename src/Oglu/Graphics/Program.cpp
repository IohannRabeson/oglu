/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Program.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 21:07:28 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 10:55:05 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/Program.hpp"
#include "Oglu/OpenGl/OpenGlError.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
    Program::Program() :
        m_programId(glCreateProgram())
    {
        checkGlError(__FILE__, __LINE__);
    }

    Program::~Program()
    {
        if (m_programId != 0u)
        {
            GL_CHECK( glDeleteProgram(oglu::get(m_programId)) );
        }
    }

    GLuint	Program::getId()const
    {
        return (oglu::get(m_programId));
    }

    void Program::use()
    {
        m_used = true;
        GL_CHECK( glUseProgram(oglu::get(m_programId)) );
    }

    void Program::unuse()
    {
        m_used = false;
        GL_CHECK( glUseProgram(0u) );
    }

    UniformId Program::getUniformLocation(std::string const& name)const
    {
        return (glGetUniformLocation(oglu::get(m_programId), name.c_str()));
    }

    AttributeId Program::getAttributeLocation(std::string const& name)const
    {
        return (glGetAttribLocation(oglu::get(m_programId), name.c_str()));
    }

    std::string Program::getInfoLog()const
    {
        std::string	result;
        GLsizei		length = 0u;

        glGetProgramiv(oglu::get(m_programId), GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char buffer[length + 1];

            glGetProgramInfoLog(oglu::get(m_programId), length, nullptr, buffer);
            result.assign(buffer);
            if (result.back() == '\n')
            {
                result.pop_back();
            }
        }
        return (result);
    }

    void Program::setUniform(UniformId id, float v0)
    {
        assert(m_used);

        glUniform1f(oglu::get(id), v0);
    }

    void Program::setUniform(UniformId id, float v0, float v1)
    {
        assert(m_used);

        glUniform2f(oglu::get(id), v0, v1);
    }

    void Program::setUniform(UniformId id, float v0, float v1, float v2)
    {
        assert(m_used);

        glUniform3f(oglu::get(id), v0, v1, v2);
    }

    void Program::setUniform(UniformId id, float v0, float v1, float v2, float v3)
    {
        assert(m_used);

        glUniform4f(oglu::get(id), v0, v1, v2, v3);
    }

    void Program::setUniform(UniformId id, float const* array, GLsizei size)
    {
        assert(m_used);

        glUniform1fv(oglu::get(id), size, array);
    }

    void Program::setUniform(UniformId id, std::vector<float> const& array)
    {
        assert(m_used);
        assert(array.size() <= std::numeric_limits<GLsizei>::max());

        glUniform1fv(oglu::get(id), static_cast<GLsizei>(array.size()), array.data());
    }

    void Program::setUniform(UniformId id, int v0)
    {
        assert(m_used);

        glUniform1i(oglu::get(id), v0);
    }

    void Program::setUniform(UniformId id, int v0, int v1)
    {
        assert(m_used);

        glUniform2i(oglu::get(id), v0, v1);
    }

    void Program::setUniform(UniformId id, int v0, int v1, int v2)
    {
        assert(m_used);

        glUniform3i(oglu::get(id), v0, v1, v2);
    }

    void Program::setUniform(UniformId id, int v0, int v1, int v2, int v3)
    {
        assert(m_used);

        glUniform4i(oglu::get(id), v0, v1, v2, v3);
    }

    void Program::setUniform(UniformId id, int const* array, GLsizei size)
    {
        assert(m_used);

        glUniform1iv(oglu::get(id), size, array);
    }

    void Program::setUniform(UniformId id, std::vector<int> const& array)
    {
        assert(m_used);
        assert(array.size() <= std::numeric_limits<GLsizei>::max());

        glUniform1iv(oglu::get(id), static_cast<GLsizei>(array.size()), array.data());
    }


    void Program::setUniform(UniformId id, unsigned int v0)
    {
        assert(m_used);

        glUniform1ui(oglu::get(id), v0);
    }

    void Program::setUniform(UniformId id, unsigned int v0, unsigned int v1)
    {
        assert(m_used);

        glUniform2ui(oglu::get(id), v0, v1);
    }

    void Program::setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2)
    {
        assert(m_used);

        glUniform3ui(oglu::get(id), v0, v1, v2);
    }

    void Program::setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
    {
        assert(m_used);

        glUniform4ui(oglu::get(id), v0, v1, v2, v3);
    }

    void Program::setUniform(UniformId id, unsigned int const* array, GLsizei size)
    {
        assert(m_used);

        glUniform1uiv(oglu::get(id), size, array);
    }

    void Program::setUniform(UniformId id, std::vector<unsigned int> const& array)
    {
        assert(m_used);
        assert(array.size() <= std::numeric_limits<GLsizei>::max());

        glUniform1uiv(oglu::get(id), static_cast<GLsizei>(array.size()), array.data());
    }

    void Program::setUniform(UniformId id, glm::vec2 const& vec)
    {
        assert(m_used);

        glUniform2fv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::vec3 const& vec)
    {
        assert(m_used);

        glUniform3fv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::vec4 const& vec)
    {
        assert(m_used);

        glUniform4fv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::ivec2 const& vec)
    {
        assert(m_used);

        glUniform2iv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::ivec3 const& vec)
    {
        assert(m_used);

        glUniform3iv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::ivec4 const& vec)
    {
        assert(m_used);

        glUniform4iv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::uvec2 const& vec)
    {
        assert(m_used);

        glUniform2uiv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::uvec3 const& vec)
    {
        assert(m_used);

        glUniform3uiv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::uvec4 const& vec)
    {
        assert(m_used);

        glUniform4uiv(oglu::get(id), 1u, glm::value_ptr(vec));
    }

    void Program::setUniform(UniformId id, glm::mat2 const& mat)
    {
        assert(m_used);

        glUniformMatrix2fv(oglu::get(id), 1u, GL_FALSE, glm::value_ptr(mat));
    }

    void Program::setUniform(UniformId id, glm::mat3 const& mat)
    {
        assert(m_used);

        glUniformMatrix3fv(oglu::get(id), 1u, GL_FALSE, glm::value_ptr(mat));
    }

    void Program::setUniform(UniformId id, glm::mat4 const& mat)
    {
        assert(m_used);

        glUniformMatrix4fv(oglu::get(id), 1u, GL_FALSE, glm::value_ptr(mat));
    }

    void Program::forEachUniformInfo(std::function<void (const Program::UniformInfo &)> &&f) const
    {
        for (auto const& kv : m_uniformInfos)
        {
            f(kv.second);
        }
    }

    void Program::forEachAttributeInfo(std::function<void (const Program::AttributeInfo &)> &&f) const
    {
        for (auto const& kv : m_attributeInfos)
        {
            f(kv.second);
        }
    }

    void Program::gatherUniformInfos()
    {
        GLuint count = 0;
        GLsizei const bufferSize = 256;
        std::unique_ptr<char[]> buffer(new char[bufferSize]);

        GL_CHECK( glGetProgramiv(oglu::get(m_programId), GL_ACTIVE_UNIFORMS, reinterpret_cast<GLint*>(&count)) );
        for (auto i = 0u; i < count; ++i)
        {
            GLint size = 0;
            GLenum type = 0;

            GL_CHECK( glGetActiveUniform(oglu::get(m_programId), i, bufferSize, nullptr, &size, &type, buffer.get()) );

            std::string const name{buffer.get()};
            UniformId const id{i};

            m_uniformIdentifiers.emplace(name, UniformId{i});
            m_uniformInfos.emplace(id, UniformInfo{name, id, size, type});
        }
    }

    void Program::gatherAttributeInfos()
    {
        GLuint count = 0;
        GLsizei const bufferSize = 256;
        std::unique_ptr<char[]> buffer(new char[bufferSize]);

        GL_CHECK( glGetProgramiv(oglu::get(m_programId), GL_ACTIVE_ATTRIBUTES, reinterpret_cast<GLint*>(&count)) );
        for (auto i = 0u; i < count; ++i)
        {
            GLint size = 0;
            GLenum type = 0;

            GL_CHECK( glGetActiveAttrib(oglu::get(m_programId), i, bufferSize, nullptr, &size, &type, buffer.get()) );

            std::string const name{buffer.get()};
            AttributeId const id{i};

            m_attributeIdentifiers.emplace(name, id);
            m_attributeInfos.emplace(id, AttributeInfo{name, id, size, type});
        }
    }
}
