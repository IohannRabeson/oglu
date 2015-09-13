/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 22:41:20 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/13 21:58:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_WINDOW_HPP
# define OGLU_WINDOW_HPP
# include "Oglu/OpenGl.hpp"
# include "Oglu/ContextSettings.hpp"
# include "Oglu/KeyModifier.hpp"
# include "Oglu/MouseButton.hpp"

# include <glm/glm.hpp>

# include <string>
# include <vector>

namespace oglu
{
	class IWindowListener;
	class IKeyboardListener;
	class IMouseListener;

	class Window
	{
	public:
		enum class CursorMode : int
		{
			Enabled = GLFW_CURSOR_NORMAL,
			Hidden = GLFW_CURSOR_HIDDEN,
			Disabled = GLFW_CURSOR_DISABLED
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
		std::vector<IWindowListener*>	m_windowListeners;
		std::vector<IKeyboardListener*>	m_keyboardListeners;
		std::vector<IMouseListener*>	m_mouseListeners;
		GLFWwindow*						m_window;
		GLbitfield						m_clearMode;							
	};
}

#endif
