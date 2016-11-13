/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContextSettings.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/29 00:05:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/08 14:54:59 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_CONTEXTSETTINGS_HPP
# define OGLU_CONTEXTSETTINGS_HPP

namespace oglu
{
	class ContextSettings
	{
	public:
		explicit ContextSettings(int contextVersionMajor = 4,
								 int contextVersionMinor = 1,
								 int antialiasingLevel = 0,
								 bool depthBuffer = true);

		int		getContextVersionMajor()const;
		int		getContextVersionMinor()const;
		int		getAntialisingLevel()const;
		bool	isDepthBufferEnabled()const;
	private:
        int	const m_contextVersionMajor;
        int const m_contextVersionMinor;
        int const m_antialiasingLevel;
        bool const m_depthBuffer;
	};
}

#endif
