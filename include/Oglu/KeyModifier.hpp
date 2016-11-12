/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyModifier.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 20:20:14 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 02:22:44 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMODIFIER_HPP
# define KEYMODIFIER_HPP
# include "Oglu/OpenGl.hpp"
# include "Oglu/Flags.hpp"

namespace oglu
{
	/*!
		\brief Modified key flags
	 */
	enum KeyModifier
	{
		Shift = GLFW_MOD_SHIFT,
		Control = GLFW_MOD_CONTROL,
		Alt = GLFW_MOD_ALT,
		Super = GLFW_MOD_SUPER
	};

	typedef Flags<KeyModifier, int>	KeyModifiers;
}

#endif
