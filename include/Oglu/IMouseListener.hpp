/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMouseListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/10 20:00:03 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 01:19:42 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMOUSELISTENER_HPP
# define IMOUSELISTENER_HPP
# include "OpenGl.hpp"
# include "KeyModifier.hpp"
# include "MouseButton.hpp"

namespace oglu
{
	class IMouseListener
	{
	public:
		virtual ~IMouseListener()
		{
		}

		virtual void	onMouseMoved(double x, double y) = 0;
		virtual void	onMouseEntered() = 0;
		virtual void	onMouseLeaved() = 0;
		virtual void	onMousePressed(MouseButton button, KeyModifier modifiers) = 0;
		virtual void	onMouseReleased(MouseButton button, KeyModifier modifiers) = 0;
	};
}

#endif
