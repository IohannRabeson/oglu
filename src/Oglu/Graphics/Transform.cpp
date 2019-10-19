/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 18:29:41 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/20 18:29:58 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Graphics/Transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

oglu::Transform const oglu::Transform::Identity = Transform();
glm::mat4 const oglu::Transform::IdentityMatrix = glm::mat4(1.f);

void oglu::Transform::setPosition(const glm::vec3 &position)
{
    m_position = position;
    m_updateCache = true;
}

void oglu::Transform::translate(const glm::vec3 &offset)
{
    m_position += offset;
    m_updateCache = true;
}

void oglu::Transform::setRotation(const glm::quat &rotation)
{
    m_rotation = rotation;
    m_updateCache = true;
}

void oglu::Transform::setRotation(float degres, const glm::vec3 &axis)
{
    m_rotation = glm::rotate(glm::quat(), degres, axis);
    m_updateCache = true;
}

void oglu::Transform::rotate(float degres, const glm::vec3 &axis)
{
    m_rotation = glm::rotate(m_rotation, degres, axis);
    m_updateCache = true;
}

void oglu::Transform::setScale(const glm::vec3 &scale)
{
    m_scale = scale;
    m_updateCache = true;
}

const glm::vec3 &oglu::Transform::getPosition() const
{
    return m_position;
}

const glm::quat &oglu::Transform::getRotation() const
{
    return m_rotation;
}

const glm::vec3 &oglu::Transform::getScale() const
{
    return m_scale;
}

const glm::mat4 &oglu::Transform::getMatrix() const
{
    updateCache();
    return m_matrix;
}

void oglu::Transform::updateCache() const
{
    if (m_updateCache == false)
        return;
    m_matrix = glm::scale(IdentityMatrix, m_scale) * glm::toMat4(m_rotation) * glm::translate(IdentityMatrix, m_position);
    m_updateCache = false;
}
