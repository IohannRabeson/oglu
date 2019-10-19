/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProgramTest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:42:54 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/20 01:00:46 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <Oglu/Graphics/Program.hpp>
#include <Oglu/Graphics/Shader.hpp>
#include <Oglu/Window/Window.hpp>
#include <Oglu/Graphics/Mesh.hpp>

BOOST_AUTO_TEST_SUITE(mesh_model)

class ColorVertexShader : public oglu::AShaderLoader
{
    std::string getShaderContent() override
    {
        return std::string
        {
            "#version 330 core\n"
            "layout(location = 0) in vec3	vertexPosition;\n"
            "layout(location = 1) in vec3	vertexColor;\n"
            "\n"
            "uniform mat4    camera;\n"
            "out vec3        fragmentColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = camera * vec4(vertexPosition, 1.0);\n"
            "    fragmentColor = vertexColor;\n"
            "}\n"
        };
    }
};

class ColorFragmentShader : public oglu::AShaderLoader
{
    std::string getShaderContent() override
    {
        return std::string
        {
            "#version 330 core\n"
            "\n"
            "in vec3     fragmentColor;\n"
            "out vec3    color;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    color = fragmentColor;\n"
            "}\n"
        };
    }
};

/*!
    \brief Check only if MeshModel is buildable.
 */
BOOST_AUTO_TEST_CASE( trivial )
{
    oglu::Window render;

    if (render.create(2880, 1800, "Test", false, oglu::ContextSettings(4, 1, 0)) == false)
    {
        std::cerr << "Create window failed" << std::endl;
        return;
    }

    oglu::Mesh<oglu::MeshComponents::Position,
               oglu::MeshComponents::Color,
               oglu::MeshComponents::Index,
               oglu::MeshComponents::Normal,
               oglu::MeshComponents::TextureUV> model;
}

BOOST_AUTO_TEST_SUITE_END()
