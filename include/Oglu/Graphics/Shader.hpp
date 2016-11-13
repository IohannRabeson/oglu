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
# include "Oglu/OpenGl.hpp"
# include "Oglu/Generics/StrongInteger.hpp"
# include <string>

namespace oglu
{
    using ShaderId = StrongInteger<GLint, struct ShaderTag>;

	template <GLenum Type>
	class Shader
	{
	public:
		explicit Shader();
		~Shader();

        void setSource(std::string const& source);
        void compile();

        ShaderId getId()const;
		std::string	getInfoLog()const;
	private:
        ShaderId m_shaderId;
	};
}

#include "Oglu/Graphics/Shader.hxx"
#endif
