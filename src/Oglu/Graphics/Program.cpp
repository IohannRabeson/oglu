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
#include "Oglu/OpenGlError.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace oglu
{
	Program::Program() :
		m_programId(0u)
	{
		GL_CHECK( m_programId = glCreateProgram() );
	}

	Program::~Program()
	{
		if (m_programId != 0u)
		{
			GL_CHECK( glDeleteProgram(m_programId) );
		}
	}

	GLuint	Program::getId()const
	{
		return (m_programId);
	}

	void	Program::use()
	{
        m_enabled = true;
		GL_CHECK( glUseProgram(m_programId) );
	}

	void	Program::unuse()
	{
        m_enabled = false;
		GL_CHECK( glUseProgram(0u) );
	}

    UniformId Program::getUniformLocation(std::string const& name)const
	{
		return (glGetUniformLocation(m_programId, name.c_str()));
	}

    AttributeId Program::getAttributeLocation(std::string const& name)const
	{
		return (glGetAttribLocation(m_programId, name.c_str()));
	}

	std::string Program::getInfoLog()const
	{
		std::string	result;
		GLsizei		length = 0u;

		glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			char	buffer[length + 1];

			glGetProgramInfoLog(m_programId, length, nullptr, buffer);
			result.assign(buffer);
			if (result.back() == '\n')
			{
				result.pop_back();
			}
		}
		return (result);
	}

    void	Program::setUniform(UniformId id, float v0)
	{
        assert(m_enabled);

        glUniform1f(id, v0);
	}

    void	Program::setUniform(UniformId id, float v0, float v1)
	{
        assert(m_enabled);

        glUniform2f(id, v0, v1);
	}

    void	Program::setUniform(UniformId id, float v0, float v1, float v2)
	{
        assert(m_enabled);

        glUniform3f(id, v0, v1, v2);
	}

    void	Program::setUniform(UniformId id, float v0, float v1, float v2, float v3)
	{
        assert(m_enabled);

        glUniform4f(id, v0, v1, v2, v3);
	}
	
    void	Program::setUniform(UniformId id, float const* array, std::size_t size)
	{
        assert(m_enabled);

        glUniform1fv(id, size, array);
	}
	
    void	Program::setUniform(UniformId id, std::vector<float> const& array)
	{
        assert(m_enabled);

        glUniform1fv(id, array.size(), array.data());
	}

    void	Program::setUniform(UniformId id, int v0)
	{
        assert(m_enabled);

        glUniform1i(id, v0);
	}

    void	Program::setUniform(UniformId id, int v0, int v1)
	{
        assert(m_enabled);

        glUniform2i(id, v0, v1);
	}

    void	Program::setUniform(UniformId id, int v0, int v1, int v2)
	{
        assert(m_enabled);

        glUniform3i(id, v0, v1, v2);
	}

    void	Program::setUniform(UniformId id, int v0, int v1, int v2, int v3)
	{
        assert(m_enabled);

        glUniform4i(id, v0, v1, v2, v3);
	}

    void	Program::setUniform(UniformId id, int const* array, std::size_t size)
	{
        assert(m_enabled);

        glUniform1iv(id, size, array);
	}
	
    void	Program::setUniform(UniformId id, std::vector<int> const& array)
	{
        assert(m_enabled);

        glUniform1iv(id, array.size(), array.data());
	}


    void	Program::setUniform(UniformId id, unsigned int v0)
	{
        assert(m_enabled);

        glUniform1ui(id, v0);
	}

    void	Program::setUniform(UniformId id, unsigned int v0, unsigned int v1)
	{
        assert(m_enabled);

        glUniform2ui(id, v0, v1);
	}

    void	Program::setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2)
	{
        assert(m_enabled);

        glUniform3ui(id, v0, v1, v2);
	}

    void	Program::setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
	{
        assert(m_enabled);

        glUniform4ui(id, v0, v1, v2, v3);
	}

    void	Program::setUniform(UniformId id, unsigned int const* array, std::size_t size)
	{
        assert(m_enabled);

        glUniform1uiv(id, size, array);
	}
	
    void	Program::setUniform(UniformId id, std::vector<unsigned int> const& array)
	{
        assert(m_enabled);

        glUniform1uiv(id, array.size(), array.data());
	}

    void	Program::setUniform(UniformId id, glm::vec2 const& vec)
	{
        assert(m_enabled);

        glUniform2fv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::vec3 const& vec)
	{
        assert(m_enabled);

        glUniform3fv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::vec4 const& vec)
	{
        assert(m_enabled);

        glUniform4fv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::ivec2 const& vec)
	{
        assert(m_enabled);

        glUniform2iv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::ivec3 const& vec)
	{
        assert(m_enabled);

        glUniform3iv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::ivec4 const& vec)
	{
        assert(m_enabled);

        glUniform4iv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::uvec2 const& vec)
	{
        assert(m_enabled);

        glUniform2uiv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::uvec3 const& vec)
	{
        assert(m_enabled);

        glUniform3uiv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::uvec4 const& vec)
	{
        assert(m_enabled);

        glUniform4uiv(id, 1u, glm::value_ptr(vec));
	}

    void	Program::setUniform(UniformId id, glm::mat2 const& mat)
	{
        assert(m_enabled);

        glUniformMatrix2fv(id, 1u, GL_FALSE, glm::value_ptr(mat));
	}

    void	Program::setUniform(UniformId id, glm::mat3 const& mat)
	{
        assert(m_enabled);

        glUniformMatrix3fv(id, 1u, GL_FALSE, glm::value_ptr(mat));
	}

    void	Program::setUniform(UniformId id, glm::mat4 const& mat)
	{
        assert(m_enabled);

        glUniformMatrix4fv(id, 1u, GL_FALSE, glm::value_ptr(mat));
	}
}
