/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/08 16:01:20 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/14 02:00:29 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Oglu/OpenGl/OpenGl.hpp>
#include <Oglu/Window/Window.hpp>
#include <Oglu/Graphics/Shader.hpp>
#include <Oglu/Graphics/Program.hpp>
#include <Oglu/Graphics/Camera.hpp>
#include <Oglu/Graphics/Mesh.hpp>
#include <Oglu/Graphics/RgbaColor.hpp>
#include <Oglu/Graphics/Transform.hpp>
#include <Oglu/Graphics/ObjMeshLoader.hpp>
#include <Oglu/Graphics/PlyMeshLoader.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

#include <glm/ext.hpp>

using Mesh = oglu::Mesh<oglu::MeshComponents::Position, oglu::MeshComponents::Normal>;

int main( void )
{
    oglu::Window render;

    if (render.create(2880, 1800, "Test", false, oglu::ContextSettings(4, 1, 0)) == false)
    {
        std::cerr << "Create window failed" << std::endl;
        return (1);
    }

    oglu::Program program;
    oglu::Camera camera(45.f, 2880, 1800);
    std::vector<Mesh> meshes(8u);
    std::vector<oglu::Transform> transforms(8u, oglu::Transform::Identity);

    float lastTime = 0.f;
    float currentTime = 0.f;
    float frameTime = 0.f;
    float mouseSens = 0.1;
    glm::dvec2 mousePos;
    float moveSpeed = 2.f;

    try
    {
        program.link(oglu::Shader<oglu::ShaderType::Vertex>(oglu::LoadShaderFromFile("shaders/loaders.vert")),
                     oglu::Shader<oglu::ShaderType::Fragment>(oglu::LoadShaderFromFile("shaders/loaders.frag")));

        auto const uniformMVPMatrix = program.getUniformLocation("Matrix_MVP");
        auto const uniformModelMatrix = program.getUniformLocation("Matrix_M");
        auto const lightPosition = program.getUniformLocation("LightPosition");

        camera.setPosition(0.f, 0.f, 5.f);

        for (auto& mesh : meshes)
        {
            mesh.setAttribute<oglu::MeshComponents::Position>(program.getAttributeLocation("vertexPosition"));
            mesh.setAttribute<oglu::MeshComponents::Normal>(program.getAttributeLocation("vertexNormal"));
            mesh.load(oglu::PlyMeshLoader<Mesh>("models/susan_color.ply"));
        }
        for (auto i = 0u; i < transforms.size(); ++i)
        {
            transforms[i].setPosition(glm::vec3(i * 1.61803398875f * 3.f, 0.f, 0.f));
        }
        render.setCursorPosition(glm::dvec2(0, 0));
        render.setCursorMode(oglu::Window::CursorMode::Disabled);

        while (render.isOpen())
        {
            render.pollEvents();
            render.clear();
            program.use();

            auto transformIt = transforms.begin();
            for (auto const& mesh : meshes)
            {
                program.setUniform(uniformModelMatrix, transformIt->getMatrix());
                program.setUniform(uniformMVPMatrix, camera.getViewProjectionMatrix() * transformIt->getMatrix());
                program.setUniform(lightPosition, glm::vec3(0, 10.0, 0));
                mesh.render();
                ++transformIt;
            }
            program.unuse();
            render.display();
            // Mouse control
            mousePos = render.getCursorPosition();
            render.setCursorPosition(glm::dvec2(0, 0));
            camera.rotateYaw(mousePos.x * mouseSens);
            camera.rotatePitch(mousePos.y * mouseSens / 2.f);
            // Key control
            if (render.isKeyPressed(GLFW_KEY_W))
            {
                camera.move(frameTime * moveSpeed * camera.getFront());
            }
            else if (render.isKeyPressed(GLFW_KEY_S))
            {
                camera.move(frameTime * -moveSpeed * camera.getFront());
            }
            if (render.isKeyPressed(GLFW_KEY_D))
            {
                camera.move(frameTime * moveSpeed * camera.getRight());
            }
            else if (render.isKeyPressed(GLFW_KEY_A))
            {
                camera.move(frameTime * -moveSpeed * camera.getRight());
            }
            if (render.isKeyPressed(GLFW_KEY_R))
            {
                camera.move(frameTime * moveSpeed * camera.getUp());
            }
            else if (render.isKeyPressed(GLFW_KEY_F))
            {
                camera.move(frameTime * -moveSpeed * camera.getUp());
            }
            frameTime = currentTime - lastTime;
            lastTime = currentTime;
            currentTime = glfwGetTime();
        }
    }
    catch (std::runtime_error const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}

