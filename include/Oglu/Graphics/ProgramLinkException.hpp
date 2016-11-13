/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProgramLinkException.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 10:39:17 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 10:44:02 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAMLINKEXCEPTION_HPP
# define PROGRAMLINKEXCEPTION_HPP
# include <stdexcept>

namespace oglu
{
	class ProgramLinkException : public std::runtime_error
	{
	public:
		explicit ProgramLinkException(std::string const& log);
	};
}

#endif
