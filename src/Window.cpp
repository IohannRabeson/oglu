/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 22:59:10 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 02:22:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Window.hpp"
#include "Oglu/IWindowListener.hpp"
#include "Oglu/IKeyboardListener.hpp"
#include "Oglu/IMouseListener.hpp"
#include "Oglu/OpenGlError.hpp"
#include "Oglu/Shader.hpp"

#include <algorithm>
#include <iostream>

namespace oglu
{
	namespace
	{
		static inline Window*	getWindowFromGLFWwindow(GLFWwindow* window)
		{
			return (static_cast<Window*>(glfwGetWindowUserPointer(window)));
		}

		void errorCallback(int error, const char* description)
		{
			std::cerr << "GLFW error: " << error << ": " << description << std::endl;
		}
	}

	/*!	Create a Window instance. */
	Window::Window() :
		m_window(nullptr),
		m_clearMode(ClearMode::ColorBuffer),
		m_clearColor(0.f, 0.f, 0.f, 1.f)
	{
	}

	/*!	Close the window. */
	Window::~Window()
	{
		close();
		glfwTerminate();
	}

	/*!	Create or recreate a window.
	  	\param width The width of the window
		\param height The height of the window
		\param title Title displayed in the title bar
		\param fullscreen Set true to enable fullscreen mode
		\param settings OpenGL context settings
		\return false if the window can't be created
		\see ContextSettings
	*/
	bool	Window::create(int width, int height, std::string const& title,
						   bool fullscreen, ContextSettings&& settings)
	{
		bool			isOk = false;
		GLFWmonitor*	monitor = nullptr;

		if (glfwInit() == GL_FALSE)
		{
			return (false);
		}
		glfwWindowHint(GLFW_SAMPLES, settings.getAntialisingLevel());
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.getContextVersionMajor());
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.getContextVersionMinor());
		// Note: this line is required to use OpenGl > 2.1 with MacOS
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
		glfwSetErrorCallback(errorCallback);
		if (fullscreen)
		{
			monitor = glfwGetPrimaryMonitor();
			GLFWvidmode const*	mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			width = mode->width;
			height = mode->height;
		}
		m_window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
		glfwMakeContextCurrent(m_window);
		glewExperimental = GL_TRUE; // Needed for core profile
		if (m_window && glewInit() == GLEW_OK)
		{
			glGetError();
			if (settings.isDepthBufferEnabled())
			{
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS); // TODO: remove (default value is GL_LESS)
				m_clearMode = static_cast<ClearMode>(m_clearMode | ClearMode::DepthBuffer);
			}
			// TODO: when an Application class will comes this line
			// will should be removed.
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowCloseCallback(m_window, &Window::windowClosedCallback);
			glfwSetWindowFocusCallback(m_window, &Window::windowFocusCallback);
			glfwSetWindowPosCallback(m_window, &Window::windowMovedCallback);
			glfwSetWindowSizeCallback(m_window, &Window::windowResizedCallback);
			glfwSetKeyCallback(m_window, &Window::keyboardCallback);
			isOk = true;
		}
		return (isOk);
	}

	/*!	Close the window. */
	void	Window::close()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
	}

	/*! Return true if the window is open. */
	bool	Window::isOpen()const
	{
		return (m_window != nullptr && glfwWindowShouldClose(m_window) == 0);
	}

	/*!	Clear the render by filling it with a color.

	  	The mode and the color can be set with setClearColor() and setClearColor().
	 */
	void	Window::clear()
	{
		glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
		glClear(static_cast<GLbitfield>(m_clearMode));
	}

	/*! Flush render to the screen. */
	void	Window::display()
	{
		glfwSwapBuffers(m_window);
	}

	/*!	Poll events and dispatchs them. */
	void	Window::pollEvents()
	{
		glfwPollEvents();
	}

	//								  //
	// --- Properties --- 			  //
	//								  //

	/*!	Set the cursor mode. */
	void	Window::setCursorMode(CursorMode mode)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, static_cast<int>(mode));
	}

	/*!
		Set the buffers cleared when clear() is called.
	*/
	void	Window::setClearMode(ClearModes mode)
	{
		m_clearMode = mode;
	}

	/*!
		Set the color used to fill the render.
	*/
	void	Window::setClearColor(glm::vec4 const& color)
	{
		m_clearColor = color;
	}

	/*!	Return the cursor position. */
	glm::dvec2	Window::getCursorPosition()const
	{
		glm::dvec2	pos;

		glfwGetCursorPos(m_window, &pos.x, &pos.y);
		return (pos);
	}

	/*!	Return the key state. */
	bool	Window::isKeyPressed(int key)const
	{
		return (glfwGetKey(m_window, key));
	}

	/*!	Set the cursor position. */
	void	Window::setCursorPosition(glm::dvec2 const& pos)
	{
		glfwSetCursorPos(m_window, pos.x, pos.y);
	}

	//								  //
	// --- Listeners registration --- //
	//								  //

	/*!
		Register an IWindowListener instance.
	*/
	void	Window::registerWindowListener(IWindowListener* listener)
	{
		if (std::find(m_windowListeners.begin(), m_windowListeners.end(), listener) == m_windowListeners.end())
		{
			m_windowListeners.push_back(listener);
		}
	}

	/*!
		Unregister an IWindowListener instance.
	*/
	void	Window::unregisterWindowListener(IWindowListener* listener)
	{
		auto	it = std::find(m_windowListeners.begin(), m_windowListeners.end(), listener);

		if (it != m_windowListeners.end())
		{
			m_windowListeners.erase(it);
		}
	}

	/*!
		Register an IKeyboardListener instance.
	*/
	void	Window::registerKeyboardListener(IKeyboardListener* listener)
	{
		if (std::find(m_keyboardListeners.begin(), m_keyboardListeners.end(), listener) == m_keyboardListeners.end())
		{
			m_keyboardListeners.push_back(listener);
		}
	}

	/*!
		Unregister an IKeyboardListener instance.
	*/
	void	Window::unregisterKeyboardListener(IKeyboardListener* listener)
	{
		auto	it = std::find(m_keyboardListeners.begin(), m_keyboardListeners.end(), listener);

		if (it != m_keyboardListeners.end())
		{
			m_keyboardListeners.erase(it);
		}
	}

	/*!
		Register an IMouseListener instance.
	*/
	void	Window::registerMouseListener(IMouseListener* listener)
	{
		if (std::find(m_mouseListeners.begin(), m_mouseListeners.end(), listener) == m_mouseListeners.end())
		{
			m_mouseListeners.push_back(listener);
		}
	}

	/*!
		Unregister an IMouseListener instance.
	*/
	void	Window::unregisterMouseListener(IMouseListener* listener)
	{
		auto	it = std::find(m_mouseListeners.begin(), m_mouseListeners.end(), listener);

		if (it != m_mouseListeners.end())
		{
			m_mouseListeners.erase(it);
		}
	}

	void	Window::notifyWindowClosed()
	{
		for (auto* listener : m_windowListeners)
		{
			listener->onWindowClosed();
		}
	}

	void	Window::notifyWindowMoved(int x, int y)
	{
		for (auto* listener : m_windowListeners)
		{
			listener->onWindowMoved(x, y);
		}
	}

	void	Window::notifyWindowResized(int width, int height)
	{
		for (auto* listener : m_windowListeners)
		{
			listener->onWindowResized(width, height);
		}
	}

	void	Window::notifyWindowFocusGained()
	{
		for (auto* listener : m_windowListeners)
		{
			listener->onWindowFocusGained();
		}
	}

	void	Window::notifyWindowFocusLost()
	{
		for (auto* listener : m_windowListeners)
		{
			listener->onWindowFocusLost();
		}
	}

	void	Window::notifyKeyPressed(int key, KeyModifiers modifiers)
	{
		for (auto* listener : m_keyboardListeners)
		{
			listener->onKeyPressed(key, modifiers);
		}
	}

	void	Window::notifyKeyReleased(int key, KeyModifiers modifiers)
	{
		for (auto* listener : m_keyboardListeners)
		{
			listener->onKeyReleased(key, modifiers);
		}
	}

	void	Window::notifyMouseMoved(double x, double y)
	{
		for (auto* listener : m_mouseListeners)
		{
			listener->onMouseMoved(x, y);
		}
	}

	void	Window::notifyMouseEntered()
	{
		for (auto* listener : m_mouseListeners)
		{
			listener->onMouseEntered();
		}
	}

	void	Window::notifyMouseLeaved()
	{
		for (auto* listener : m_mouseListeners)
		{
			listener->onMouseLeaved();
		}
	}

	void	Window::notifyMousePressed(MouseButton button, KeyModifiers modifiers)
	{
		for (auto* listener : m_mouseListeners)
		{
			listener->onMousePressed(button, modifiers);
		}
	}

	void	Window::notifyMouseReleased(MouseButton button, KeyModifiers modifiers)
	{
		for (auto* listener : m_mouseListeners)
		{
			listener->onMouseReleased(button, modifiers);
		}
	}

	void	Window::windowClosedCallback(GLFWwindow* window)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		render->notifyWindowClosed();
	}

	void	Window::windowMovedCallback(GLFWwindow* window, int x, int y)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		render->notifyWindowMoved(x, y);
	}

	void	Window::windowResizedCallback(GLFWwindow* window, int width, int height)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		render->notifyWindowResized(width, height);
	}

	void	Window::windowFocusCallback(GLFWwindow* window, int state)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		if (state == GL_TRUE)
		{
			render->notifyWindowFocusGained();
		}
		else
		{
			render->notifyWindowFocusLost();
		}
	}

	void	Window::keyboardCallback(GLFWwindow* window, int key, int, int action, int modifiers)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		if (key == GLFW_KEY_UNKNOWN)
		{
			return;
		}
		switch (action)
		{
			case GLFW_PRESS:
				render->notifyKeyPressed(key, modifiers);
				break;
			case GLFW_RELEASE:
				render->notifyKeyReleased(key, modifiers);
				break;
			default:
				break;
		}
	}

	void	Window::mouseMovedCallback(GLFWwindow* window, double x, double y)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		render->notifyMouseMoved(x, y);
	}

	void	Window::mouseFocusCallback(GLFWwindow* window, int entered)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		if (entered)
		{
			render->notifyMouseEntered();
		}
		else
		{
			render->notifyMouseLeaved();
		}
	}

	void	Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
	{
		Window* const	render = getWindowFromGLFWwindow(window);

		switch(action)
		{
		case GLFW_PRESS:
			render->notifyMousePressed(static_cast<MouseButton>(button), modifiers);
			break;
		case GLFW_RELEASE:
			render->notifyMouseReleased(static_cast<MouseButton>(button), modifiers);
			break;
		default:
			break;
		}
	}
}
