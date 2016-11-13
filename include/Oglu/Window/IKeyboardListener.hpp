/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IKeyboardListener.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/29 04:01:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/10 20:38:36 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_IKEYBOARDLISTENER_HPP
# define OGLU_IKEYBOARDLISTENER_HPP
# include "Oglu/Window/KeyModifier.hpp"

namespace oglu
{
	class IKeyboardListener
	{
	public:
        virtual ~IKeyboardListener();

		virtual void	onKeyPressed(int key, KeyModifier modifiers) = 0;
		virtual void	onKeyReleased(int key, KeyModifier modifiers) = 0;
	};
}

#endif
