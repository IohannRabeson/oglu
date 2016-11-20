/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 22:41:20 by irabeson          #+#    #+#             */
/*   Updated: 2016/02/01 01:12:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_WINDOW_HPP
# define OGLU_WINDOW_HPP
# include "Oglu/OpenGl/OpenGl.hpp"
# include "Oglu/Window/ContextSettings.hpp"
# include "Oglu/Window/KeyModifier.hpp"
# include "Oglu/Window/MouseButton.hpp"

# include <glm/glm.hpp>

# include <string>
# include <vector>
# include <memory>

namespace oglu
{
	class IWindowListener;
	class IKeyboardListener;
	class IMouseListener;

	/*!
	  	\brief Manage a window on screen

		To initialize a window call create().<br>
		Window can be closed by calling close() method.<br>
		<h2>Events dispatch</h2>
		The window own the responsability of dispatching events to listeners.<br>
		Events dispatch must be triggered by the user each frame by calling pollEvents().

		<h2>Drawing</h2>
		Before all render must be cleaned by calling clear().<br>
		Then draw with OpenGL and call display() to render to the screen.<br>
		\see IWindowListener, IKeyboardListener and IMouseListener

		<h2>Typical main loop</h2>
		The following listing show a typical main loop.<br>
		\code
		oglu::Window						render;

		if (render.create(2880, 1800, "Test", false, oglu::ContextSettings(4, 1, 0)) == false)
		{
			std::cerr << "Create window failed" << std::endl;
			return (1);
		}
		try
		{
			while (render.isOpen())
			{
				render.pollEvents();
				render.clear();
				// Draw here...
				render.display();
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
		\endcode
	*/
	class Window
	{
	public:
		enum class CursorMode : int
		{
			Enabled = GLFW_CURSOR_NORMAL,
			Hidden = GLFW_CURSOR_HIDDEN,
			Disabled = GLFW_CURSOR_DISABLED
		};

		enum ClearMode
		{
			ColorBuffer = GL_COLOR_BUFFER_BIT,
			DepthBuffer = GL_DEPTH_BUFFER_BIT,
			StencilBuffer = GL_STENCIL_BUFFER_BIT
		};

		Window();
		~Window();

		bool		create(int width, int height,
						   std::string const& title,
						   bool fullscreen,
						   ContextSettings&& settings = ContextSettings());
		void		close();
		bool		isOpen()const;

		void		clear();
		void		display();
		void		pollEvents();

		void		setCursorMode(CursorMode mode);
		void		setClearMode(ClearMode mode);
		void		setClearColor(glm::vec4 const& color);

		void		setCursorPosition(glm::dvec2 const& pos);
		glm::dvec2	getCursorPosition()const;

		bool		isKeyPressed(int key)const;

		void		registerWindowListener(IWindowListener* listener);
		void		unregisterWindowListener(IWindowListener* listener);
		void		registerKeyboardListener(IKeyboardListener* listener);
		void		unregisterKeyboardListener(IKeyboardListener* listener);
		void		registerMouseListener(IMouseListener* listener);
		void		unregisterMouseListener(IMouseListener* listener);
	private:
		// TODO: use glm vec when it is possible
		void		notifyWindowClosed();
		void		notifyWindowMoved(int x, int y);
		void		notifyWindowResized(int width, int height);
		void		notifyWindowFocusGained();
		void		notifyWindowFocusLost();
		void		notifyKeyPressed(int key, KeyModifier modifiers);
		void		notifyKeyReleased(int key, KeyModifier modifiers);
		void		notifyMouseEntered();
		void		notifyMouseLeaved();
		void		notifyMousePressed(MouseButton button, KeyModifier modifiers);
		void		notifyMouseReleased(MouseButton button, KeyModifier modifiers);
		void		notifyMouseMoved(double x, double y);

		static void	windowClosedCallback(GLFWwindow* window);
		static void	windowMovedCallback(GLFWwindow* window, int x, int y);
		static void	windowResizedCallback(GLFWwindow* window, int width, int height);
		static void	windowFocusCallback(GLFWwindow* window, int state);
		static void	keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
		static void	mouseMovedCallback(GLFWwindow* window, double x, double y);
		static void	mouseFocusCallback(GLFWwindow* window, int entered);
		static void	mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
	private:
        struct WindowDeleter
        {
            void operator()(GLFWwindow* window);
        };

        std::vector<IWindowListener*> m_windowListeners;
		std::vector<IKeyboardListener*>	m_keyboardListeners;
        std::vector<IMouseListener*> m_mouseListeners;
        std::unique_ptr<GLFWwindow, WindowDeleter> m_window;
        GLbitfield m_clearMode;
		glm::vec4						m_clearColor;
	};
}

#endif
