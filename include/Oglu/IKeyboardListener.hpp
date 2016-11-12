/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IKeyboardListener.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/29 04:01:44 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 02:14:04 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_IKEYBOARDLISTENER_HPP
# define OGLU_IKEYBOARDLISTENER_HPP
# include "Oglu/KeyModifier.hpp"

namespace oglu
{
	/*!
		\brief Listener for key pressed and key released events.
	*/
	class IKeyboardListener
	{
	public:
		virtual ~IKeyboardListener()
		{
		}

		virtual void	onKeyPressed(int key, KeyModifiers modifiers) = 0;
		virtual void	onKeyReleased(int key, KeyModifiers modifiers) = 0;
	};
}

#endif
