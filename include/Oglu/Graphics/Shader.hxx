/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hxx                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 19:35:16 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 10:55:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/OpenGlError.hpp"
#include "Oglu/Graphics/ShaderCompilationException.hpp"

namespace oglu
{
	namespace
	{
		template <GLenum Type>
		struct	ShaderTypeTraits;

		template <>
		struct	ShaderTypeTraits<GL_VERTEX_SHADER>
		{
			static constexpr char const* const	TypeName = "Vertex shader";
		};

		template <>
		struct	ShaderTypeTraits<GL_FRAGMENT_SHADER>
		{
			static constexpr char const* const	TypeName = "Fragment shader";
		};

		template <>
		struct	ShaderTypeTraits<GL_GEOMETRY_SHADER>
		{
			static constexpr char const* const	TypeName = "Geometry shader";
		};
	}

	template <GLenum Type>
	Shader<Type>::Shader() :
		m_shaderId(0u)
	{
		GL_CHECK( m_shaderId = glCreateShader(Type) );
	}

	template <GLenum Type>
	Shader<Type>::~Shader()
	{
		GL_CHECK( glDeleteShader(m_shaderId) );
	}

	template <GLenum Type>
	void	Shader<Type>::setSource(std::string const& source)
	{
		GLchar const*	str = source.c_str();

		GL_CHECK( glShaderSource(m_shaderId, 1, &str, 0) );
	}

	template <GLenum Type>
	void	Shader<Type>::compile()
	{
		GLint	result = GL_FALSE;

		GL_CHECK( glCompileShader(m_shaderId) );
		GL_CHECK( glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &result) );
		if (result == false)
		{
			throw ShaderCompilationException(ShaderTypeTraits<Type>::TypeName, getInfoLog());
		}
	}

	template <GLenum Type>
    ShaderId Shader<Type>::getId()const
	{
		return (m_shaderId);
	}

	template <GLenum Type>
	std::string	Shader<Type>::getInfoLog()const
	{
		GLsizei		length = 0u;
		std::string	result;

		glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			char	buffer[length + 1];

			glGetShaderInfoLog(m_shaderId, length, nullptr, buffer);
			result.assign(buffer);
			if (result.back() == '\n')
			{
				result.pop_back();
			}
		}
		return (result);
	}
}
