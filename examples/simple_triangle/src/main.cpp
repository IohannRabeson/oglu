/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/08 16:01:20 by irabeson          #+#    #+#             */
/*   Updated: 2016/01/02 18:34:08 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Oglu/OpenGl/OpenGl.hpp>
#include <Oglu/Window/Window.hpp>
#include <Oglu/Graphics/Shader.hpp>
#include <Oglu/Graphics/Program.hpp>
#include <Oglu/Graphics/Camera.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

#include <glm/ext.hpp>

int main( void )
{
    oglu::Window render;

    if (render.create(2880, 1800, "Test", true, oglu::ContextSettings(4, 1, 0)) == false)
    {
        std::cerr << "Create window failed" << std::endl;
        return (1);
    }
    oglu::Shader<oglu::ShaderType::Vertex> vertShader;
    oglu::Shader<oglu::ShaderType::Fragment> fragShader;
    oglu::Program program;
    oglu::Camera camera(60.f, 2880, 1800);

    GLuint VertexArrayID = 0;
    GLuint vertexBuffer = 0;
    GLuint colorBuffer = 0;

    try
    {
        vertShader.load(oglu::LoadShaderFromFile("shaders/simple_triangle.vert"));
        fragShader.load(oglu::LoadShaderFromFile("shaders/simple_triangle.frag"));
        program.link(std::move(vertShader), std::move(fragShader));

        auto const vertexPositionId = program.getAttributeLocation("vertexPosition");
        auto const vertexColorId = program.getAttributeLocation("vertexColor");
        camera.setPosition(0.f, 0.f, 2.f);
        static const GLfloat positionBufferData[] = {
             0.0f, 1.0f, 0.0f,
             -1.0f, -1.0f, 0.0f,
             1.0f,  -1.0f, 0.0f,
        };

        static const GLfloat colorBufferData[] = {
             1.0f, 0.0f, 0.0f,
             0.0f, 1.0f, 0.0f,
             0.0f,  0.0f, 1.0f,
        };

        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positionBufferData), positionBufferData, GL_STATIC_DRAW);

        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

        // 1rst attribute buffer : position
        glEnableVertexAttribArray(oglu::get(vertexPositionId));
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            oglu::get(vertexPositionId), 	// The attribute we want to configure
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(oglu::get(vertexColorId));
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(
            oglu::get(vertexColorId),      // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glBindVertexArray(0);

        auto const uniformCamera = program.getUniformLocation("camera");

        while (render.isOpen())
        {
            render.clear();
            program.use();
            program.setUniform(uniformCamera, camera.getViewProjectionMatrix());
            glBindVertexArray(VertexArrayID);
            glEnableVertexAttribArray(oglu::get(vertexPositionId));
            glEnableVertexAttribArray(oglu::get(vertexColorId));
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
            glDisableVertexAttribArray(oglu::get(vertexPositionId));
            glDisableVertexAttribArray(oglu::get(vertexColorId));
            glBindVertexArray(0);

            render.display();
            render.pollEvents();
        }
    }
    catch (std::runtime_error const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    GL_CHECK( glDeleteBuffers(1, &vertexBuffer) );
    GL_CHECK( glDeleteBuffers(1, &colorBuffer) );
    GL_CHECK( glDeleteVertexArrays(1, &VertexArrayID) );
    return (0);
}

