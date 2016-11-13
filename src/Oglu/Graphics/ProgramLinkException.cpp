/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProgramLinkException.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 10:39:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 10:42:27 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/ProgramLinkException.hpp"
#include <string>

namespace oglu
{
	ProgramLinkException::ProgramLinkException(std::string const& log) :
		std::runtime_error("Program link error: \n" + log)
	{
	}
}
