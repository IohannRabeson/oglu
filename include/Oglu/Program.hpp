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

# include <string>
# include <vector>
# include <array>

# include <glm/glm.hpp>

namespace oglu
{
	template <GLenum Type>
	class Shader;

	class Program
	{
	public:
		Program();
		~Program();

		GLuint		getId()const;

		template <GLenum ... Types>
		void		link(Shader<Types> const& ... shaders);

		std::string getInfoLog()const;

		void		use();
		void		unuse();

		GLint		getUniformLocation(std::string const& name)const;
		GLint		getAttributeLocation(std::string const& name)const;

		void		setUniform(std::string const& name, float v0);
		void		setUniform(std::string const& name, float v0, float v1);
		void		setUniform(std::string const& name, float v0, float v1, float v2);
		void		setUniform(std::string const& name, float v0, float v1, float v2, float v3);
		void		setUniform(std::string const& name, float const* array, std::size_t size); 
		void		setUniform(std::string const& name, std::vector<float> const& array); 

		void		setUniform(std::string const& name, int v0);
		void		setUniform(std::string const& name, int v0, int v1);
		void		setUniform(std::string const& name, int v0, int v1, int v2);
		void		setUniform(std::string const& name, int v0, int v1, int v2, int v3);
		void		setUniform(std::string const& name, int const* array, std::size_t size); 
		void		setUniform(std::string const& name, std::vector<int> const& array); 

		void		setUniform(std::string const& name, unsigned int v0);
		void		setUniform(std::string const& name, unsigned int v0, unsigned int v1);
		void		setUniform(std::string const& name, unsigned int v0, unsigned int v1, unsigned int v2);
		void		setUniform(std::string const& name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
		void		setUniform(std::string const& name, unsigned int const* array, std::size_t size); 
		void		setUniform(std::string const& name, std::vector<unsigned int> const& array); 

		void		setUniform(std::string const& name, glm::vec2 const& vec);
		void		setUniform(std::string const& name, glm::vec3 const& vec);
		void		setUniform(std::string const& name, glm::vec4 const& vec);

		void		setUniform(std::string const& name, glm::ivec2 const& vec);
		void		setUniform(std::string const& name, glm::ivec3 const& vec);
		void		setUniform(std::string const& name, glm::ivec4 const& vec);

		void		setUniform(std::string const& name, glm::uvec2 const& vec);
		void		setUniform(std::string const& name, glm::uvec3 const& vec);
		void		setUniform(std::string const& name, glm::uvec4 const& vec);

		void		setUniform(std::string const& name, glm::mat2 const& mat);
		void		setUniform(std::string const& name, glm::mat3 const& mat);
		void		setUniform(std::string const& name, glm::mat4 const& mat);

		template <class T, std::size_t N>
		void		setUniform(std::string const& name, std::array<T, N> const& array)
		{
			setUniform(name, array.data(), N);
		}
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
		GLuint	m_programId;
	};
}

#include "Oglu/Program.hxx"
#endif
