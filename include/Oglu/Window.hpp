/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 22:41:20 by irabeson          #+#    #+#             */
/*   Updated: 2015/09/10 21:59:23 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OGLU_WINDOW_HPP
# define OGLU_WINDOW_HPP
# include "Oglu/OpenGl.hpp"
# include "Oglu/ContextSettings.hpp"
# include "Oglu/KeyModifier.hpp"
# include "Oglu/MouseButton.hpp"

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

		void		registerWindowListener(IWindowListener* listener);
		void		unregisterWindowListener(IWindowListener* listener);
		void		registerKeyboardListener(IKeyboardListener* listener);
		void		unregisterKeyboardListener(IKeyboardListener* listener);
		void		registerMouseListener(IMouseListener* listener);
		void		unregisterMouseListener(IMouseListener* listener);
	private:
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
