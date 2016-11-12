/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderCompilationException.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 01:44:15 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 02:44:51 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERCOMPILATIONEXCEPTION_HPP
# define SHADERCOMPILATIONEXCEPTION_HPP
# include <stdexcept>

namespace oglu
{
	/*!
		Thrown when a shader compilation fail
	 */
	class ShaderCompilationException : public std::runtime_error
	{
	public:
		ShaderCompilationException(std::string const& shaderType, std::string const& log);
	};
}

#endif
