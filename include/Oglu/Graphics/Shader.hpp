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
# include "Oglu/OpenGl/OpenGl.hpp"
# include <string>

namespace oglu
{
    class AShaderLoader;

    template <ShaderType Type>
    class Shader
    {
    public:
        explicit Shader();
        explicit Shader(AShaderLoader&& loader);
        ~Shader();

        /*!
         * \brief Load then compile the shader
         * \exception ShaderCompilationException If compilation fails
         */
        void load(AShaderLoader&& loader);

        ShaderId getId()const noexcept;
        std::string	getInfoLog()const;
    private:
        void compile();
    private:
        ShaderId const m_shaderId;
        bool m_compiled = false;
    };
}

#include "Oglu/Graphics/Shader.hxx"
#endif
