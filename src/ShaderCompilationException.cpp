/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderCompilationException.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 01:45:22 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 11:50:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/ShaderCompilationException.hpp"
#include <string>

namespace oglu
{
	ShaderCompilationException::ShaderCompilationException(std::string const& shaderType,
														   std::string const& log) :
		std::runtime_error(shaderType + std::string(" compilation error:\n") + log)
	{
	}
}
