/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 18:55:50 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/14 02:07:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP
# include <glm/glm.hpp>

namespace oglu
{
	class Camera
	{
	public:
		Camera(float fov, int screenWidth, int screenHeight, float near = 0.1f, float far = 100.f);

		void				setPosition(float x, float y, float z);
		void				setPosition(glm::vec3 const& pos);
		void				move(glm::vec3 const& offset);
		void				setYaw(float angle);
		void				setPitch(float angle);
		void				rotateYaw(float offset);
		void				rotatePitch(float offset);
		
		void				setViewportSize(int width, int height);
		void				setFov(float fov);

		glm::vec3 const&	getUp()const;
		glm::vec3 const&	getForward()const;
		glm::vec3			getFront()const;
		glm::vec3			getRight()const;
		glm::mat4 const&	getMatrix()const;
	private:
		void				normalizeAngles();
	private:
		mutable glm::mat4	m_viewMatrix;
		mutable glm::mat4	m_projectionMatrix;
		mutable glm::mat4	m_cameraMatrix;
		mutable glm::vec3	m_direction;
		glm::vec3			m_position;
		glm::vec3			m_up;
		float				m_fov;				//<	Field of view in degrees
		float				m_aspectRatio;	
		float				m_near;
		float				m_far;
        float				m_yaw;              //<	Horizontal angle in degrees(yaw)
		float				m_pitch;			//<	Vertical angle in degrees(pitch)
		mutable bool		m_viewDirty;
		mutable bool		m_projectionDirty;
		mutable bool		m_cameraDirty;
	};
}

#endif
