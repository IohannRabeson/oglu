/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContextSettings.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/29 00:05:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/08 16:21:29 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/ContextSettings.hpp"

namespace oglu
{
	ContextSettings::ContextSettings(int contextVersionMajor,
									 int contextVersionMinor,
									 int antialiasingLevel,
									 bool depthBuffer) :
		m_contextVersionMajor(contextVersionMajor),
		m_contextVersionMinor(contextVersionMinor),
		m_antialiasingLevel(antialiasingLevel),
		m_depthBuffer(depthBuffer)
	{
	}

	int	ContextSettings::getContextVersionMajor()const
	{
		return (m_contextVersionMajor);
	}

	int	ContextSettings::getContextVersionMinor()const
	{
		return (m_contextVersionMinor);
	}

	int	ContextSettings::getAntialisingLevel()const
	{
		return (m_antialiasingLevel);
	}

	bool ContextSettings::isDepthBufferEnabled()const
	{
		return (m_depthBuffer);
	}
}
