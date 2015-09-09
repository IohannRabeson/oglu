/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 19:33:53 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 01:55:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_SHADER_HPP
# define OGLU_SHADER_HPP

namespace oglu
{
	template <GLenum Type>
	class Shader
	{
	public:
		explicit Shader();
		~Shader();

		void		setSource(std::string const& source);
		void		compile();

		GLuint		getId()const;
		std::string	getInfoLog()const;
	private:
		GLuint	m_shaderId;
	};
}

#include "Oglu/Shader.hxx"
#endif
