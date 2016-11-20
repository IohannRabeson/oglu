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
# include "Oglu/OpenGl/OpenGl.hpp"
# include "Oglu/Generics/StrongInteger.hpp"

# include <string>
# include <vector>
# include <array>
# include <map>
# include <functional>

# include <glm/glm.hpp>

namespace oglu
{
    enum class ShaderType : GLenum;

    template <ShaderType Type>
    class Shader;

    class Program
    {
    public:
        struct UniformInfo
        {
            std::string const name; ///< \brief Parameter name
            UniformId const identifier; ///< \brief Parameter identifier
            GLint const size; ///< \brief Parameter size
            GLenum const type; ///< \brief Parameter type
        };

        struct AttributeInfo
        {
            std::string const name; ///< \brief Parameter name
            AttributeId const identifier; ///< \brief Parameter identifier
            GLint const size; ///< \brief Parameter size
            GLenum const type; ///< \brief Parameter type
        };

        Program();
        Program(Program const&) = delete;
        Program& operator = (Program const&) = delete;
        ~Program();

        GLuint getId()const;

        /*!
         *  Links shaders.
         *
         *  Informations about uniforms are also gathered.
         *  \code
         *  program.link(vertexShader, fragmentShader);
         *  program.link(fragmentShader, vertexShader);
         *  program.link(vertexShader);
         *  program.link(fragmentShader);
         *  \endcode
         */
        template <ShaderType ... Types>
        void link(Shader<Types> const& ... shaders);

        std::string getInfoLog()const;

        void use();
        void unuse();

        AttributeId getAttributeLocation(std::string const& name)const;
        UniformId getUniformLocation(std::string const& name)const;

        void setUniform(UniformId id, float v0);
        void setUniform(UniformId id, float v0, float v1);
        void setUniform(UniformId id, float v0, float v1, float v2);
        void setUniform(UniformId id, float v0, float v1, float v2, float v3);
        void setUniform(UniformId id, float const* array, GLsizei size);
        void setUniform(UniformId id, std::vector<float> const& array);

        void setUniform(UniformId id, int v0);
        void setUniform(UniformId id, int v0, int v1);
        void setUniform(UniformId id, int v0, int v1, int v2);
        void setUniform(UniformId id, int v0, int v1, int v2, int v3);
        void setUniform(UniformId id, int const* array, GLsizei size);
        void setUniform(UniformId id, std::vector<int> const& array);

        void setUniform(UniformId id, unsigned int v0);
        void setUniform(UniformId id, unsigned int v0, unsigned int v1);
        void setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2);
        void setUniform(UniformId id, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
        void setUniform(UniformId id, unsigned int const* array, GLsizei size);
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

        /*! Overload dedicated to the arrays of uniforms. */
        template <class T, std::size_t N>
        void setUniform(UniformId id, std::array<T, N> const& array);

        /*! Iterate on each uniform information gathered while linking. */
        void forEachUniformInfo(std::function<void(UniformInfo const&)> &&f)const;

        /*! Iterate on each attribute information gathered while linking. */
        void forEachAttributeInfo(std::function<void(AttributeInfo const&)> &&f)const;
    private:
        template <ShaderType Type, ShaderType ... Types>
        inline void	attachImp(Shader<Type> const& shader, Shader<Types> const& ... shaders);

        template <ShaderType Type>
        inline void	attachImp(Shader<Type> const& shader);

        template <ShaderType Type, ShaderType ... Types>
        inline void	detachImp(Shader<Type> const& shader, Shader<Types> const& ... shaders);

        template <ShaderType Type>
        inline void	detachImp(Shader<Type> const& shader);

        void gatherUniformInfos();
        void gatherAttributeInfos();
    private:
        std::map<std::string, UniformId> m_uniformIdentifiers;
        std::map<UniformId, UniformInfo> m_uniformInfos;
        std::map<std::string, AttributeId> m_attributeIdentifiers;
        std::map<AttributeId, AttributeInfo> m_attributeInfos;

        ProgramId const m_programId;
        bool m_used = false;
    };
}

#include "Oglu/Graphics/Program.hxx"
#endif
