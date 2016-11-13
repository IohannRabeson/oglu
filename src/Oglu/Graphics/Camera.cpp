/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 21:07:15 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/14 02:14:30 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/Camera.hpp"
#include <glm/ext.hpp>
#include <cmath>

namespace oglu
{
	static inline glm::vec3	getDirection(float yaw, float pitch)
	{
		glm::vec3	direction;

		direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		direction.y = std::sin(glm::radians(pitch));
		direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		return (direction);
	}

	Camera::Camera(float fov, int screenWidth, int screenHeight, float near, float far) :
		m_direction(0.f, 0.f, -1.f),
		m_up(0.f, 1.f, 0.f),
		m_fov(fov),
		m_aspectRatio(static_cast<float>(screenWidth) / static_cast<float>(screenHeight)),
		m_near(near),
		m_far(far),
		m_yaw(-90.f),
		m_pitch(0.f),
		m_viewDirty(true),
		m_projectionDirty(true),
		m_cameraDirty(true)
	{
	}
	
	void	Camera::setPosition(float x, float y, float z)
	{
		m_position = glm::vec3(x, y, z);
		m_viewDirty = true;
		m_cameraDirty = true;
	}

	void	Camera::setPosition(glm::vec3 const& pos)
	{
		m_position = pos;
		m_viewDirty = true;
		m_cameraDirty = true;
	}

	void	Camera::move(glm::vec3 const& offset)
	{
		m_position += offset;
		m_viewDirty = true;
		m_cameraDirty = true;
	}

	void	Camera::setYaw(float angle)
	{
		m_yaw = angle;
		normalizeAngles();
		m_viewDirty = true;
		m_cameraDirty = true;
	}

	void	Camera::setPitch(float angle)
	{
		m_pitch = angle;
		normalizeAngles();
		m_viewDirty = true;
		m_cameraDirty = true;
	}
	
	void	Camera::rotateYaw(float offset)
	{
		m_yaw += offset;
		normalizeAngles();
		m_viewDirty = true;
		m_cameraDirty = true;
	}

	void	Camera::rotatePitch(float offset)
	{
		m_pitch += offset;
		normalizeAngles();
		m_viewDirty = true;
		m_cameraDirty = true;
	}

	void	Camera::setViewportSize(int width, int height)
	{
		m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		m_projectionDirty = true;
		m_cameraDirty = true;
	}

	void	Camera::setFov(float fov)
	{
		m_fov = fov;
		m_projectionDirty = true;
		m_cameraDirty = true;
	}

	glm::vec3 const&	Camera::getUp()const
	{
		return (m_up);
	}

	glm::vec3 const&	Camera::getForward()const
	{
		return (m_direction);
	}

	glm::vec3	Camera::getRight()const
	{
		return (glm::normalize(glm::cross(m_direction, m_up)));
	}

	glm::vec3	Camera::getFront()const
	{
		return (getDirection(m_yaw, 0.f));
	}

	glm::mat4 const&	Camera::getMatrix()const
	{
		if (m_projectionDirty)
		{
			m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
			m_projectionDirty = false;
		}
		if (m_viewDirty)
		{
			m_direction = getDirection(m_yaw, m_pitch);
			m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
			m_viewDirty = false;
		}
		if (m_cameraDirty)
		{
			m_cameraMatrix = m_projectionMatrix * m_viewMatrix;
			m_cameraDirty = false;
		}
		return (m_cameraMatrix);
	}

	void	Camera::normalizeAngles()
	{
		if (m_yaw > 360.f)
		{
			m_yaw -= 360.f;
		}
		else if (m_yaw < 0.f)
		{
			m_yaw += 360.f;
		}
		if (m_pitch > 89.f)
		{
			m_pitch = 89.f;
		}
		else if (m_pitch < -89.f)
		{
			m_pitch = -89.f;
		}
	}
}
