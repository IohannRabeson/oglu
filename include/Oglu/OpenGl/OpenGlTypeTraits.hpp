/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTraits.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 22:38:23 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/13 22:38:29 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined TYPETRAITS_HPP
# define TYPETRAITS_HPP
# include "Oglu/OpenGl/OpenGl.hpp"

namespace oglu
{
    template <typename T>
    struct OpenGlTypeTraits;

    template <>
    struct OpenGlTypeTraits<GLfloat>
    {
        static constexpr GLenum const Enum = GL_FLOAT;
        static constexpr bool const CanBeNormalized = true;
    };

    template <>
    struct OpenGlTypeTraits<GLdouble>
    {
        static constexpr GLenum const Enum = GL_DOUBLE;
        static constexpr bool CanBeNormalized = true;
    };

    template <>
    struct OpenGlTypeTraits<GLbyte>
    {
        static constexpr GLenum const Enum = GL_BYTE;
        static constexpr bool CanBeNormalized = false;
    };

    template <>
    struct OpenGlTypeTraits<GLubyte>
    {
        static constexpr GLenum const Enum = GL_UNSIGNED_BYTE;
        static constexpr bool CanBeNormalized = false;
    };

    template <>
    struct OpenGlTypeTraits<GLshort>
    {
        static constexpr GLenum const Enum = GL_SHORT;
        static constexpr bool CanBeNormalized = false;
    };

    template <>
    struct OpenGlTypeTraits<GLushort>
    {
        static constexpr GLenum const Enum = GL_UNSIGNED_SHORT;
        static constexpr bool CanBeNormalized = false;
    };

    template <>
    struct OpenGlTypeTraits<GLint>
    {
        static constexpr GLenum const Enum = GL_INT;
        static constexpr bool CanBeNormalized = false;
    };

    template <>
    struct OpenGlTypeTraits<GLuint>
    {
        static constexpr GLenum const Enum = GL_UNSIGNED_INT;
        static constexpr bool CanBeNormalized = false;
    };
}

#endif
