/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyModifier.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 20:20:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/10 20:54:33 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMODIFIER_HPP
# define KEYMODIFIER_HPP
# include "Oglu/OpenGl.hpp"

namespace oglu
{
	enum class KeyModifier : int
	{
		Shift = GLFW_MOD_SHIFT,
		Control = GLFW_MOD_CONTROL,
		Alt = GLFW_MOD_ALT,
		Super = GLFW_MOD_SUPER
	};
}

#endif
