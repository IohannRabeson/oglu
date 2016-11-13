/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Program.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/06 21:06:53 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/12 10:38:41 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_PROGRAM_HPP
# define OGLU_PROGRAM_HPP
# include "Oglu/OpenGl.hpp"
# include "Oglu/Generics/StrongInteger.hpp"

# include <string>
# include <vector>
# include <array>

# include <glm/glm.hpp>

namespace oglu
{
    using UniformId = StrongInteger<GLint, struct UniformTag>;
    using AttributeId = StrongInteger<GLint, struct AttributeTag>;

	template <GLenum Type>
	class Shader;

	class Program
	{
	public:
		Program();
		~Program();

        GLuint getId()const;

		template <GLenum ... Types>
        void link(Shader<Types> const& ... shaders);

		std::string getInfoLog()const;

        void use();
        void unuse();

        UniformId getUniformLocation(std::string const& name)const;
        AttributeId getAttributeLocation(std::string const& name)const;

        void setUniform(UniformId id, float v0);
        void setUniform(UniformId id, float v0, float v1);
        void setUniform(UniformId id, float v0, float v1, float v2);
        void setUniform(UniformId id, float v0, float v1, float v2, float v3);
        void setUniform(UniformId id, float const* array, std::size_t size);
        void setUniform(UniformId id, std::vector<float> const& array);

        void setUniform(UniformId id, int v0);
        void setUniform(UniformId id, int v0, int v1);
        void setUniform(UniformId id, int v0, int v1, int v2);
        void setUniform(UniformId id, int v0, int v1, int v2, int v3);
        void setUniform(UniformId id, int const* array, std::size_t size);
        void setUniform(UniformId id, std::vector<int> const& array);

        void setUniform(UniformId id, unsigned int v0);
        void setUniform(UniformId id, unsigned int v0, unsigned int v1);
        void setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2);
        void setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
        void setUniform(UniformId id, unsigned int const* array, std::size_t size);
        void setUniform(UniformId id, std::vector<unsigned int> const& array);

        void setUniform(UniformId id, glm::vec2 const& vec);
        void setUniform(UniformId id, glm::vec3 const& vec);
        void setUniform(UniformId id, glm::vec4 const& vec);

        void setUniform(UniformId id, glm::ivec2 const& vec);
        void setUniform(UniformId id, glm::ivec3 const& vec);
        void setUniform(UniformId id, glm::ivec4 const& vec);

        void setUniform(UniformId id, glm::uvec2 const& vec);
        void setUniform(UniformId id, glm::uvec3 const& vec);
        void setUniform(UniformId id, glm::uvec4 const& vec);

        void setUniform(UniformId id, glm::mat2 const& mat);
        void setUniform(UniformId id, glm::mat3 const& mat);
        void setUniform(UniformId id, glm::mat4 const& mat);

        /*!
         *  Overload dedicated to unform array.
         */
		template <class T, std::size_t N>
        void		setUniform(UniformId id, std::array<T, N> const& array);
	private:
		template <GLenum Type, GLenum ... Types>
		inline void	attachImp(Shader<Type> const& shader, Shader<Types> const& ... shaders);

		template <GLenum Type>
		inline void	attachImp(Shader<Type> const& shader);

		template <GLenum Type, GLenum ... Types>
		inline void	detachImp(Shader<Type> const& shader, Shader<Types> const& ... shaders);

		template <GLenum Type>
		inline void	detachImp(Shader<Type> const& shader);
	private:
        GLuint m_programId;
        bool m_enabled = false;
	};
}

#include "Oglu/Graphics/Program.hxx"
#endif
