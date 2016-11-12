/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGlError.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 17:41:39 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 02:13:07 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLERROR_HPP
# define OPENGLERROR_HPP
# include "OpenGl.hpp"
# include <iostream>
# include <iomanip>

/*!
	\def GL_CHECK( expression )
	\brief Display information when an OpenGL error occurs.

	This macro has no effects in Release mode, expression is executed errors
	are not tracked.

	Function glGetError() is used be carefull do not call this function yourself.
 */
# if ! defined NDEBUG
# 	define GL_CHECK( expression ) expression; checkGlError(__FILE__, __LINE__);
# else
# 	define GL_CHECK( expression ) expression;
# endif

static inline void	checkGlError(char const* file, std::size_t line)
{
	auto	errorId = glGetError();

	while (errorId != GL_NO_ERROR)
	{
		switch(errorId)
		{
			case GL_INVALID_ENUM:
				std::cerr << file << ":" << line << ": OpenGl error: GL_INVALID_ENUM" << std::endl;
				break;
			case GL_INVALID_VALUE:
				std::cerr << file << ":" << line << ": OpenGl error: GL_INVALID_VALUE" << std::endl;
				break;
			case GL_INVALID_OPERATION:
				std::cerr << file << ":" << line << ": OpenGl error: GL_INVALID_OPERATION" << std::endl;
				break;
			case GL_STACK_OVERFLOW:
				std::cerr << file << ":" << line << ": OpenGl error: GL_STACK_OVERFLOW" << std::endl;
				break;
			case GL_STACK_UNDERFLOW:
				std::cerr << file << ":" << line << ": OpenGl error: GL_STACK_UNDERFLOW" << std::endl;
				break;
			case GL_OUT_OF_MEMORY:
				std::cerr << file << ":" << line << ": OpenGl error: GL_OUT_OF_MEMORY" << std::endl;
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cerr << file << ":" << line << ": OpenGl error: GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
				break;
			default:
				std::cerr << file << ":" << line << ": OpenGl error: " << std::setw(4) << std::hex << errorId << std::endl;
				break;
		}
		errorId = glGetError();
	}
}

#endif
