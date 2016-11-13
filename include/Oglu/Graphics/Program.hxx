/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Program.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 23:19:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 10:42:58 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/ProgramLinkException.hpp"

namespace oglu
{
    template <ShaderType ... Types>
	void	Program::link(Shader<Types> const& ... shaders)
	{
		GLint	result = GL_FALSE;
		
		attachImp(shaders...);	
        glLinkProgram(oglu::get(m_programId));
        glGetProgramiv(oglu::get(m_programId), GL_LINK_STATUS, &result);
		detachImp(shaders...);
		if (result == GL_FALSE)
		{
			throw ProgramLinkException(getInfoLog());
		}
        gatherUniformInfos();
	}

    template <ShaderType Type, ShaderType ... Types>
	void	Program::attachImp(Shader<Type> const& shader, Shader<Types> const& ... shaders)
	{
		attachImp(shader);
		attachImp(shaders...);
	}

    template <ShaderType Type>
	void	Program::attachImp(Shader<Type> const& shader)
	{
        glAttachShader(oglu::get(m_programId), oglu::get(shader.getId()));
	}

    template <ShaderType Type, ShaderType ... Types>
	void	Program::detachImp(Shader<Type> const& shader, Shader<Types> const& ... shaders)
	{
		detachImp(shader);
		detachImp(shaders...);
	}

    template <ShaderType Type>
	void	Program::detachImp(Shader<Type> const& shader)
	{
        glDetachShader(oglu::get(m_programId), oglu::get(shader.getId()));
	}

    template <class T, std::size_t N>
    void    Program::setUniform(UniformId id, std::array<T, N> const& array)
    {
        setUniform(id, array.data(), N);
    }
}
