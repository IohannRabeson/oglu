/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 19:33:53 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 02:36:05 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_SHADER_HPP
# define OGLU_SHADER_HPP

namespace oglu
{
	/*!
		\brief Shader code for single stage
	 */
	template <GLenum Type>
	class Shader
	{
	public:
		explicit Shader();
		~Shader();

		/*!	Define the GLSL source code. */
		void		setSource(std::string const& source);

		/*!	Compile the GLSL source code.
		 	\throw ShaderCompilationException if the compilation fails
		 */
		void		compile();

		GLuint		getId()const;
		std::string	getInfoLog()const;
	private:
		GLuint	m_shaderId;
	};
}

#include "Oglu/Shader.hxx"
#endif
