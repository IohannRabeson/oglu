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

#include "Oglu/OpenGl/OpenGlError.hpp"
#include "Oglu/Graphics/ShaderCompilationException.hpp"
#include "Oglu/Graphics/AShaderLoader.hpp"

namespace oglu
{
    namespace
    {
        template <ShaderType Type>
        struct	ShaderTypeTraits;

        template <>
        struct	ShaderTypeTraits<ShaderType::Vertex>
        {
            static constexpr char const* const	TypeName = "Vertex shader";
        };

        template <>
        struct	ShaderTypeTraits<ShaderType::Fragment>
        {
            static constexpr char const* const	TypeName = "Fragment shader";
        };

        template <>
        struct	ShaderTypeTraits<ShaderType::Geometry>
        {
            static constexpr char const* const	TypeName = "Geometry shader";
        };
    }

    template <ShaderType Type>
    Shader<Type>::Shader() :
        m_shaderId(glCreateShader(static_cast<GLenum>(Type)))
    {
        checkGlError(__FILE__, __LINE__);
    }

    /*! Load an compile a shader. */
    template <ShaderType Type>
    Shader<Type>::Shader(AShaderLoader&& loader) :
        Shader()
    {
        load(std::move(loader));
        compile();
    }

    template <ShaderType Type>
    Shader<Type>::~Shader()
    {
        GL_CHECK( glDeleteShader(oglu::get(m_shaderId)) );
    }

    template <ShaderType Type>
    void Shader<Type>::load(AShaderLoader&& loader)
    {
        std::string const content = loader.getShaderContent();
        GLchar const* const str = content.c_str();

        m_compiled = false;
        GL_CHECK( glShaderSource(oglu::get(m_shaderId), 1, &str, 0) );
        compile();
    }

    template <ShaderType Type>
    void	Shader<Type>::compile()
    {
        GLint	result = GL_FALSE;

        GL_CHECK( glCompileShader(oglu::get(m_shaderId)) );
        GL_CHECK( glGetShaderiv(oglu::get(m_shaderId), GL_COMPILE_STATUS, &result) );
        if (result == GL_FALSE)
        {
            throw ShaderCompilationException(ShaderTypeTraits<Type>::TypeName, getInfoLog());
        }
        m_compiled = true;
    }

    template <ShaderType Type>
    ShaderId Shader<Type>::getId()const noexcept
    {
        return (m_shaderId);
    }

    template <ShaderType Type>
    std::string	Shader<Type>::getInfoLog()const
    {
        GLsizei		length = 0u;
        std::string	result;

        glGetShaderiv(oglu::get(m_shaderId), GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char	buffer[length + 1];

            glGetShaderInfoLog(oglu::get(m_shaderId), length, nullptr, buffer);
            result.assign(buffer);
            if (result.back() == '\n')
            {
                result.pop_back();
            }
        }
        return (result);
    }
}
