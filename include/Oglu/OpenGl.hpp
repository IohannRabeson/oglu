/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGl.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/29 01:17:26 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/09 02:17:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGL_HPP
# define OPENGL_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "Oglu/Generics/StrongInteger.hpp"

namespace oglu
{
    /*! Available shader types. */
    enum class ShaderType : GLenum
    {
        Fragment = GL_FRAGMENT_SHADER,
        Vertex = GL_VERTEX_SHADER,
        Geometry = GL_GEOMETRY_SHADER
    };

    /*! Program resource identifier. */
    using ProgramId = StrongInteger<GLuint, struct ProgramTag>;

    /*! Shader resource identifier. */
    using ShaderId = StrongInteger<GLint, struct ShaderTag>;

    /*! Uniform shader parameter identifier. */
    using UniformId = StrongInteger<GLint, struct UniformTag>;

    /*! Vertex attribute identifier. */
    using AttributeId = StrongInteger<GLint, struct AttributeTag>;
}

#endif
