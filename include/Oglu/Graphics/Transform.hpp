/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 18:29:35 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/20 18:29:40 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if!defined TRANSFORM_HPP
# define TRANSFORM_HPP
# include <glm/mat4x4.hpp>
# include <glm/vec3.hpp>
# include <glm/gtc/quaternion.hpp>
# include <glm/gtx/quaternion.hpp>
# include <glm/gtx/matrix_decompose.hpp>

namespace oglu
{
    class Transform
    {
        static glm::mat4 const IdentityMatrix;
    public:
        static Transform const Identity;

        void setPosition(glm::vec3 const& position);
        void translate(glm::vec3 const& offset);
        void setRotation(const glm::quat &rotation);
        void rotate(float degres, glm::vec3 const& axis);
        void setScale(glm::vec3 const& scale);

        glm::vec3 const& getPosition()const;
        glm::quat const& getRotation()const;
        glm::vec3 const& getScale()const;

        glm::mat4 const& getMatrix()const;
    private:
        void updateCache()const;
    private:
        glm::vec3 m_scale{1.f};
        glm::vec3 m_position;
        glm::quat m_rotation;
        mutable glm::mat4 m_matrix = glm::mat4(1.f);
        mutable bool m_updateCache = false;
    };
}

#endif
