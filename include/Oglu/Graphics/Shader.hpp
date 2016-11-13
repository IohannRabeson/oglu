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
    class AShaderLoader;

    template <ShaderType Type>
	class Shader
	{
	public:
		explicit Shader();
		~Shader();

        void load(AShaderLoader&& loader);

        /*!
         * \brief Compile the shader
         * \exception ShaderCompilationException If compilation fails
         */
        void compile();

        ShaderId getId()const;
		std::string	getInfoLog()const;
	private:
        ShaderId m_shaderId;
        bool m_compiled = false;
	};
}

#include "Oglu/Graphics/Shader.hxx"
#endif
