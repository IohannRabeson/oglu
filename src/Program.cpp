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

#include "Oglu/Program.hpp"
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
		GL_CHECK( glUseProgram(m_programId) );
	}

	void	Program::unuse()
	{
		GL_CHECK( glUseProgram(0u) );
	}

	GLint	Program::getUniformLocation(std::string const& name)const
	{
		return (glGetUniformLocation(m_programId, name.c_str()));
	}

	GLint	Program::getAttributeLocation(std::string const& name)const
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

	void	Program::setUniform(std::string const& name, float v0)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1f(location, v0);
	}

	void	Program::setUniform(std::string const& name, float v0, float v1)
	{
		GLint const	location = getUniformLocation(name);

		glUniform2f(location, v0, v1);
	}

	void	Program::setUniform(std::string const& name, float v0, float v1, float v2)
	{
		GLint const	location = getUniformLocation(name);

		glUniform3f(location, v0, v1, v2);
	}

	void	Program::setUniform(std::string const& name, float v0, float v1, float v2, float v3)
	{
		GLint const	location = getUniformLocation(name);

		glUniform4f(location, v0, v1, v2, v3);
	}
	
	void	Program::setUniform(std::string const& name, float const* array, std::size_t size)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1fv(location, size, array);
	}
	
	void	Program::setUniform(std::string const& name, std::vector<float> const& array)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1fv(location, array.size(), array.data());
	}

	void	Program::setUniform(std::string const& name, int v0)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1i(location, v0);
	}

	void	Program::setUniform(std::string const& name, int v0, int v1)
	{
		GLint const	location = getUniformLocation(name);

		glUniform2i(location, v0, v1);
	}

	void	Program::setUniform(std::string const& name, int v0, int v1, int v2)
	{
		GLint const	location = getUniformLocation(name);

		glUniform3i(location, v0, v1, v2);
	}

	void	Program::setUniform(std::string const& name, int v0, int v1, int v2, int v3)
	{
		GLint const	location = getUniformLocation(name);

		glUniform4i(location, v0, v1, v2, v3);
	}

	void	Program::setUniform(std::string const& name, int const* array, std::size_t size)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1iv(location, size, array);
	}
	
	void	Program::setUniform(std::string const& name, std::vector<int> const& array)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1iv(location, array.size(), array.data());
	}


	void	Program::setUniform(std::string const& name, unsigned int v0)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1ui(location, v0);
	}

	void	Program::setUniform(std::string const& name, unsigned int v0, unsigned int v1)
	{
		GLint const	location = getUniformLocation(name);

		glUniform2ui(location, v0, v1);
	}

	void	Program::setUniform(std::string const& name, unsigned int v0, unsigned int v1, unsigned int v2)
	{
		GLint const	location = getUniformLocation(name);

		glUniform3ui(location, v0, v1, v2);
	}

	void	Program::setUniform(std::string const& name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
	{
		GLint const	location = getUniformLocation(name);

		glUniform4ui(location, v0, v1, v2, v3);
	}

	void	Program::setUniform(std::string const& name, unsigned int const* array, std::size_t size)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1uiv(location, size, array);
	}
	
	void	Program::setUniform(std::string const& name, std::vector<unsigned int> const& array)
	{
		GLint const	location = getUniformLocation(name);

		glUniform1uiv(location, array.size(), array.data());
	}

	void	Program::setUniform(std::string const& name, glm::vec2 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform2fv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::vec3 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform3fv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::vec4 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform4fv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::ivec2 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform2iv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::ivec3 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform3iv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::ivec4 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform4iv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::uvec2 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform2uiv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::uvec3 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform3uiv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::uvec4 const& vec)
	{
		GLint const	location = getUniformLocation(name);

		glUniform4uiv(location, 1u, glm::value_ptr(vec));
	}

	void	Program::setUniform(std::string const& name, glm::mat2 const& mat)
	{
		GLint const	location = getUniformLocation(name);

		glUniformMatrix2fv(location, 1u, GL_FALSE, glm::value_ptr(mat));
	}

	void	Program::setUniform(std::string const& name, glm::mat3 const& mat)
	{
		GLint const	location = getUniformLocation(name);

		glUniformMatrix3fv(location, 1u, GL_FALSE, glm::value_ptr(mat));
	}

	void	Program::setUniform(std::string const& name, glm::mat4 const& mat)
	{
		GLint const	location = getUniformLocation(name);

		glUniformMatrix4fv(location, 1u, GL_FALSE, glm::value_ptr(mat));
	}
}
