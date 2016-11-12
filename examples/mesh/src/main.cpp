/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/08 16:01:20 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 01:22:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Oglu/OpenGl.hpp>
#include <Oglu/Window.hpp>
#include <Oglu/Shader.hpp>
#include <Oglu/Program.hpp>
#include <Oglu/Camera.hpp>
#include <Oglu/Buffer.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

#include <glm/ext.hpp>

static const std::tuple<GLfloat, GLfloat, GLfloat> positionBufferData[] =
{
	{-1.0, -1.0,  1.0},
  	{ 1.0, -1.0,  1.0},
  	{ 1.0,  1.0,  1.0},
  	{-1.0,  1.0,  1.0},
  	{-1.0, -1.0, -1.0},
  	{-1.0,  1.0, -1.0},
  	{ 1.0,  1.0, -1.0},
  	{ 1.0, -1.0, -1.0},
  	{-1.0,  1.0, -1.0},
  	{-1.0,  1.0,  1.0},
  	{ 1.0,  1.0,  1.0},
  	{ 1.0,  1.0, -1.0},
  	{-1.0, -1.0, -1.0},
  	{ 1.0, -1.0, -1.0},
  	{ 1.0, -1.0,  1.0},
  	{-1.0, -1.0,  1.0},
  	{ 1.0, -1.0, -1.0},
  	{ 1.0,  1.0, -1.0},
  	{ 1.0,  1.0,  1.0},
  	{ 1.0, -1.0,  1.0},
  	{-1.0, -1.0, -1.0},
  	{-1.0, -1.0,  1.0},
  	{-1.0,  1.0,  1.0},
  	{-1.0,  1.0, -1.0}
};

static const std::tuple<GLfloat, GLfloat, GLfloat> colorBufferData[] = {
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

	if (render.create(2880, 1800, "Test", false, oglu::ContextSettings(4, 1, 0)) == false)
	{
		std::cerr << "Create window failed" << std::endl;
		return (1);
	}
	typedef oglu::Buffer<float, float, float>	Vec3Buffer;

	oglu::Shader<GL_VERTEX_SHADER>		vertShader;
	oglu::Shader<GL_FRAGMENT_SHADER>	fragShader;
	oglu::Program						program;
	oglu::Camera						camera(45.f, 2880, 1800);

	GLuint								vertexPositionId = 0;
	GLuint								vertexColorId = 0;
	GLuint								VertexArrayID = 0;
	GLuint								positionBuffer = 0;
	GLuint								colorBuffer = 0;

	double 								lastTime = 0.f;
	double								currentTime = 0.f;
	double								frameTime = 0.f;
	double								mouseSens = 0.1;
	glm::dvec2							mousePos;
	float								moveSpeed = 2.f;
	try
	{
		vertShader.setSource(readEntireFile("shaders/camera.vert"));
		fragShader.setSource(readEntireFile("shaders/camera.frag"));
		vertShader.compile();
		fragShader.compile();
		program.link(std::move(vertShader), std::move(fragShader));

		vertexPositionId = program.getAttributeLocation("vertexPosition");
		vertexColorId = program.getAttributeLocation("vertexColor");
		camera.setPosition(0.f, 0.f, 5.f);
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		Vec3Buffer							posBuffer(positionBufferData, sizeof(positionBufferData), Vec3Buffer::Usage::DynamicDraw);
		Vec3Buffer							colBuffer(colorBufferData, sizeof(colorBufferData), Vec3Buffer::Usage::DynamicDraw);

		/*
		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positionBufferData), positionBufferData, GL_STATIC_DRAW);

		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);
		*/
		// 1rst attribute buffer : position
		glEnableVertexAttribArray(vertexPositionId);
		posBuffer.bind();
		//glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
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
		//glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		colBuffer.bind();
		glVertexAttribPointer(
			vertexColorId,      // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindVertexArray(0);
		render.setCursorPosition(glm::dvec2(0, 0));
		render.setCursorMode(oglu::Window::CursorMode::Disabled);
		while (render.isOpen())
		{
			render.pollEvents();
			render.clear();
			program.use();
			program.setUniform("camera", camera.getMatrix());
			glBindVertexArray(VertexArrayID);
			glEnableVertexAttribArray(vertexPositionId);
			glEnableVertexAttribArray(vertexColorId);
			glDrawArrays(GL_TRIANGLES, 0, 36); // 3 indices starting at 0 -> 1 triangle
			glDisableVertexAttribArray(vertexPositionId);
			glDisableVertexAttribArray(vertexColorId);
			glBindVertexArray(0);
			render.display();
			// Mouse control
			mousePos = render.getCursorPosition();
			render.setCursorPosition(glm::dvec2(0, 0));
			camera.rotateYaw(mousePos.x * mouseSens);
			camera.rotatePitch(mousePos.y * mouseSens);
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
	GL_CHECK( glDeleteBuffers(1, &positionBuffer) );
	GL_CHECK( glDeleteBuffers(1, &colorBuffer) );
	GL_CHECK( glDeleteVertexArrays(1, &VertexArrayID) );
	return (0);
}

