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

#include <Oglu/OpenGl.hpp>
#include <Oglu/Window.hpp>
#include <Oglu/Shader.hpp>
#include <Oglu/Program.hpp>
#include <Oglu/Camera.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

#include <glm/ext.hpp>

static std::string	readEntireFile(std::string const& filePath)
{
	std::ifstream	file;
	std::string		buffer;

	file.open(filePath);
	file.unsetf(std::ios_base::skipws);
	if (file.is_open())
	{
		buffer.assign(std::istream_iterator<char>(file),
					  std::istream_iterator<char>());
	}
	else
	{
		throw std::runtime_error("Unable to read file " + filePath);
	}
	return (buffer);
}

int main( void )
{
	oglu::Window						render;

	if (render.create(2880, 1800, "Test", true, oglu::ContextSettings(4, 1, 0)) == false)
	{
		std::cerr << "Create window failed" << std::endl;
		return (1);
	}
	oglu::Shader<GL_VERTEX_SHADER>		vertShader;
	oglu::Shader<GL_FRAGMENT_SHADER>	fragShader;
	oglu::Program						program;
	oglu::Camera						camera(60.f, 2880, 1800);

	GLuint								vertexPositionId = 0; 
	GLuint								vertexColorId = 0;
	GLuint								VertexArrayID = 0;
	GLuint								vertexBuffer = 0;
	GLuint								colorBuffer = 0;

	try
	{
		vertShader.setSource(readEntireFile("shaders/simple_triangle.vert"));
		fragShader.setSource(readEntireFile("shaders/simple_triangle.frag"));
		vertShader.compile();
		fragShader.compile();
		program.link(std::move(vertShader), std::move(fragShader));

		vertexPositionId = program.getAttributeLocation("vertexPosition");
		vertexColorId = program.getAttributeLocation("vertexColor");
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
		glEnableVertexAttribArray(vertexPositionId);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			vertexPositionId, 	// The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(vertexColorId);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(
			vertexColorId,      // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindVertexArray(0);
		while (render.isOpen())
		{
			render.clear();
			program.use();
			program.setUniform("camera", camera.getMatrix());
			glBindVertexArray(VertexArrayID);
			glEnableVertexAttribArray(vertexPositionId);
			glEnableVertexAttribArray(vertexColorId);
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
			glDisableVertexAttribArray(vertexPositionId);
			glDisableVertexAttribArray(vertexColorId);
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

