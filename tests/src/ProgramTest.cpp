/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProgramTest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:42:54 by irabeson          #+#    #+#             */
/*   Updated: 2016/11/13 11:44:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <Oglu/Graphics/Program.hpp>
#include <Oglu/Graphics/Shader.hpp>
#include <Oglu/Window/Window.hpp>

BOOST_AUTO_TEST_SUITE(program)

class UniformTestLoader : public oglu::AShaderLoader
{
public:
    std::string getShaderContent() override;
};

std::string UniformTestLoader::getShaderContent()
{
    return std::string
    {
        "#version 330 core\n"
        "uniform mat4 camera;\n"
        "uniform float truc;\n"
        "uniform int yop;\n"
        "void main()\n"
        "{\n"
        "gl_Position = camera * vec4(truc * yop);\n"
        "}"
    };
}

BOOST_AUTO_TEST_CASE( uniform_info )
{
    oglu::Window render;

    if (render.create(2880, 1800, "Test", false, oglu::ContextSettings(4, 1, 0)) == false)
    {
        std::cerr << "Create window failed" << std::endl;
        return;
    }

    oglu::Program program;
    std::vector<oglu::Program::UniformInfo> infos;

    program.link(oglu::Shader<oglu::ShaderType::Vertex>(UniformTestLoader()));
    program.forEachUniformInfo([&infos](oglu::Program::UniformInfo const& info)
    {
        infos.push_back(info);
    });
    // expected size: 3 ->
    // "uniform mat4 camera;\n"
    // "uniform float truc;\n"
    // "uniform int yop;\n"
    BOOST_TEST(infos.size() == 3u);
}

BOOST_AUTO_TEST_SUITE_END()
