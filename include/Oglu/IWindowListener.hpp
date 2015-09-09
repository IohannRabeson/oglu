/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IWindowListener.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/29 02:59:20 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/08 14:59:29 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_IWINDOWLISTENER_HPP
# define OGLU_IWINDOWLISTENER_HPP

namespace oglu
{
	class IWindowListener
	{
	public:
		virtual ~IWindowListener()
		{
		}

		virtual void	onWindowClosed() = 0;
		virtual void	onWindowMoved(int x, int y) = 0;
		virtual void	onWindowResized(int width, int height) = 0;
		virtual void	onWindowFocusGained() = 0;
		virtual void	onWindowFocusLost() = 0;
	};
}

#endif
