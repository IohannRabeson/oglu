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
#include <Oglu/Graphics/Color.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

#include <glm/ext.hpp>

using Mesh = oglu::Mesh<oglu::ModelComponents::Position, oglu::ModelComponents::Color>;

class CubeLoader : public Mesh::AMeshModelLoader
{
    std::vector<glm::vec3> const PositionBufferData =
    {
        {1.0f,-1.0f,-1.0f},
        {-1.0f,-1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f,-1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f, 1.0f,-1.0f},
        {1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f,-1.0f},
        {1.0f,-1.0f,-1.0f},
        {1.0f, 1.0f,-1.0f},
        {1.0f,-1.0f,-1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f,-1.0f},
        {1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f,-1.0f, 1.0f},
        {1.0f,-1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f,-1.0f,-1.0f},
        {1.0f, 1.0f,-1.0f},
        {1.0f,-1.0f,-1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f,-1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f,-1.0f},
        {-1.0f, 1.0f,-1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f,-1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f,-1.0f, 1.0f}
    };

    std::vector<oglu::Color> const ColorBufferData =
    {
        {0.583f,  0.771f,  0.014f},
        {0.609f,  0.115f,  0.436f},
        {0.327f,  0.483f,  0.844f},
        {0.822f,  0.569f,  0.201f},
        {0.435f,  0.602f,  0.223f},
        {0.310f,  0.747f,  0.185f},
        {0.597f,  0.770f,  0.761f},
        {0.559f,  0.436f,  0.730f},
        {0.359f,  0.583f,  0.152f},
        {0.483f,  0.596f,  0.789f},
        {0.559f,  0.861f,  0.639f},
        {0.195f,  0.548f,  0.859f},
        {0.014f,  0.184f,  0.576f},
        {0.771f,  0.328f,  0.970f},
        {0.406f,  0.615f,  0.116f},
        {0.676f,  0.977f,  0.133f},
        {0.971f,  0.572f,  0.833f},
        {0.140f,  0.616f,  0.489f},
        {0.997f,  0.513f,  0.064f},
        {0.945f,  0.719f,  0.592f},
        {0.543f,  0.021f,  0.978f},
        {0.279f,  0.317f,  0.505f},
        {0.167f,  0.620f,  0.077f},
        {0.347f,  0.857f,  0.137f},
        {0.055f,  0.953f,  0.042f},
        {0.714f,  0.505f,  0.345f},
        {0.783f,  0.290f,  0.734f},
        {0.722f,  0.645f,  0.174f},
        {0.302f,  0.455f,  0.848f},
        {0.225f,  0.587f,  0.040f},
        {0.517f,  0.713f,  0.338f},
        {0.053f,  0.959f,  0.120f},
        {0.393f,  0.621f,  0.362f},
        {0.673f,  0.211f,  0.457f},
        {0.820f,  0.883f,  0.371f},
        {0.982f,  0.099f,  0.879f}
    };

    void load(std::vector<oglu::ModelComponents::Position::DataType>& positions) override
    {
        positions.assign(std::begin(PositionBufferData), std::end(PositionBufferData));
    }

    void load(std::vector<oglu::ModelComponents::Color::DataType>& colors) override
    {
        colors = ColorBufferData;
    }
};

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
    Mesh mesh;

    Mesh mesh2;

    float 								lastTime = 0.f;
    float								currentTime = 0.f;
    float								frameTime = 0.f;
    float								mouseSens = 0.1;
    glm::dvec2							mousePos;
    float								moveSpeed = 2.f;
    try
    {
        program.link(oglu::Shader<oglu::ShaderType::Vertex>(oglu::LoadShaderFromFile("shaders/camera.vert")),
                     oglu::Shader<oglu::ShaderType::Fragment>(oglu::LoadShaderFromFile("shaders/camera.frag")));

        auto const uniformCamera = program.getUniformLocation("camera");

        camera.setPosition(0.f, 0.f, 5.f);

        mesh.setAttribute<oglu::ModelComponents::Position>(program.getAttributeLocation("vertexPosition"));
        mesh.setAttribute<oglu::ModelComponents::Color>(program.getAttributeLocation("vertexColor"));
        mesh.load(CubeLoader());

        mesh2.setAttribute<oglu::ModelComponents::Position>(program.getAttributeLocation("vertexPosition"));
        mesh2.setAttribute<oglu::ModelComponents::Color>(program.getAttributeLocation("vertexColor"));
        mesh2.load(CubeLoader());

        render.setCursorPosition(glm::dvec2(0, 0));
        render.setCursorMode(oglu::Window::CursorMode::Disabled);

        glm::mat4 model = glm::mat4(1.f);

        model = glm::translate(model, glm::vec3(-2.f));
        while (render.isOpen())
        {
            render.pollEvents();
            render.clear();
            program.use();
            program.setUniform(uniformCamera, camera.getMatrix() * model);
            mesh.render();
            program.setUniform(uniformCamera, camera.getMatrix());
            mesh2.render();
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
            model = glm::rotate(model, frameTime, glm::vec3(0.f, 1.f, 0.f));
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

