/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 22:59:10 by irabeson          #+#    #+#             */
/*   Updated: 2016/01/02 18:35:42 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Oglu/Window/Window.hpp"
#include "Oglu/Window/IWindowListener.hpp"
#include "Oglu/Window/IKeyboardListener.hpp"
#include "Oglu/Window/IMouseListener.hpp"
#include "Oglu/OpenGl/OpenGlError.hpp"
#include "Oglu/Graphics/Shader.hpp"

#include <algorithm>
#include <iostream>

namespace oglu
{
    namespace
    {
        static inline Window* getWindowFromGLFWwindow(GLFWwindow* window)
        {
            return (static_cast<Window*>(glfwGetWindowUserPointer(window)));
        }

        void errorCallback(int error, const char* description)
        {
            std::cerr << "GLFW error: " << error << ": " << description << std::endl;
        }
    }

    Window::Window() :
        m_window(nullptr),
        m_clearMode(GL_COLOR_BUFFER_BIT)
    {
    }

    Window::~Window()
    {
        close();
        glfwTerminate();
    }

    bool Window::create(int width, int height, std::string const& title,
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
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Note: this line is required to use OpenGl > 2.1 with MacOS
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
        m_window.reset(glfwCreateWindow(width, height, title.c_str(), monitor, nullptr));
        glfwMakeContextCurrent(m_window.get());
        glewExperimental = GL_TRUE; // Needed for core profile
        if (m_window && glewInit() == GLEW_OK)
        {
            glGetError();
            if (settings.isDepthBufferEnabled())
            {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS); // TODO: remove (default value is GL_LESS)
                m_clearMode |= GL_DEPTH_BUFFER_BIT;
            }
            // TODO: when an Application class will comes this line
            // will should be removed.
            glfwSetInputMode(m_window.get(), GLFW_STICKY_KEYS, GL_TRUE);
            glfwSetWindowUserPointer(m_window.get(), this);
            glfwSetWindowCloseCallback(m_window.get(), &Window::windowClosedCallback);
            glfwSetWindowFocusCallback(m_window.get(), &Window::windowFocusCallback);
            glfwSetWindowPosCallback(m_window.get(), &Window::windowMovedCallback);
            glfwSetWindowSizeCallback(m_window.get(), &Window::windowResizedCallback);
            glfwSetKeyCallback(m_window.get(), &Window::keyboardCallback);
            isOk = true;
        }
        return (isOk);
    }

    void Window::close()
    {
        m_window.reset();
    }

    bool Window::isOpen()const
    {
        return (m_window != nullptr && glfwWindowShouldClose(m_window.get()) == 0);
    }

    void Window::clear()
    {
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(m_clearMode);
    }


    void Window::setCursorMode(CursorMode mode)
    {
        glfwSetInputMode(m_window.get(), GLFW_CURSOR, static_cast<int>(mode));
    }

    glm::dvec2	Window::getCursorPosition()const
    {
        glm::dvec2	pos;

        glfwGetCursorPos(m_window.get(), &pos.x, &pos.y);
        return (pos);
    }

    bool Window::isKeyPressed(int key)const
    {
        return (glfwGetKey(m_window.get(), key));
    }

    void Window::setCursorPosition(glm::dvec2 const& pos)
    {
        glfwSetCursorPos(m_window.get(), pos.x, pos.y);
    }


    void Window::display()
    {
        glfwSwapBuffers(m_window.get());
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    void Window::registerWindowListener(IWindowListener* listener)
    {
        if (std::find(m_windowListeners.begin(), m_windowListeners.end(), listener) == m_windowListeners.end())
        {
            m_windowListeners.push_back(listener);
        }
    }

    void Window::unregisterWindowListener(IWindowListener* listener)
    {
        auto	it = std::find(m_windowListeners.begin(), m_windowListeners.end(), listener);

        if (it != m_windowListeners.end())
        {
            m_windowListeners.erase(it);
        }
    }

    void Window::registerKeyboardListener(IKeyboardListener* listener)
    {
        if (std::find(m_keyboardListeners.begin(), m_keyboardListeners.end(), listener) == m_keyboardListeners.end())
        {
            m_keyboardListeners.push_back(listener);
        }
    }

    void Window::unregisterKeyboardListener(IKeyboardListener* listener)
    {
        auto	it = std::find(m_keyboardListeners.begin(), m_keyboardListeners.end(), listener);

        if (it != m_keyboardListeners.end())
        {
            m_keyboardListeners.erase(it);
        }
    }

    void Window::registerMouseListener(IMouseListener* listener)
    {
        if (std::find(m_mouseListeners.begin(), m_mouseListeners.end(), listener) == m_mouseListeners.end())
        {
            m_mouseListeners.push_back(listener);
        }
    }

    void Window::unregisterMouseListener(IMouseListener* listener)
    {
        auto	it = std::find(m_mouseListeners.begin(), m_mouseListeners.end(), listener);

        if (it != m_mouseListeners.end())
        {
            m_mouseListeners.erase(it);
        }
    }

    void Window::notifyWindowClosed()
    {
        for (auto* listener : m_windowListeners)
        {
            listener->onWindowClosed();
        }
    }

    void Window::notifyWindowMoved(int x, int y)
    {
        for (auto* listener : m_windowListeners)
        {
            listener->onWindowMoved(x, y);
        }
    }

    void Window::notifyWindowResized(int width, int height)
    {
        for (auto* listener : m_windowListeners)
        {
            listener->onWindowResized(width, height);
        }
    }

    void Window::notifyWindowFocusGained()
    {
        for (auto* listener : m_windowListeners)
        {
            listener->onWindowFocusGained();
        }
    }

    void Window::notifyWindowFocusLost()
    {
        for (auto* listener : m_windowListeners)
        {
            listener->onWindowFocusLost();
        }
    }

    void Window::notifyKeyPressed(int key, KeyModifier modifiers)
    {
        for (auto* listener : m_keyboardListeners)
        {
            listener->onKeyPressed(key, modifiers);
        }
    }

    void Window::notifyKeyReleased(int key, KeyModifier modifiers)
    {
        for (auto* listener : m_keyboardListeners)
        {
            listener->onKeyReleased(key, modifiers);
        }
    }

    void Window::notifyMouseMoved(double x, double y)
    {
        for (auto* listener : m_mouseListeners)
        {
            listener->onMouseMoved(x, y);
        }
    }

    void Window::notifyMouseEntered()
    {
        for (auto* listener : m_mouseListeners)
        {
            listener->onMouseEntered();
        }
    }

    void Window::notifyMouseLeaved()
    {
        for (auto* listener : m_mouseListeners)
        {
            listener->onMouseLeaved();
        }
    }

    void Window::notifyMousePressed(MouseButton button, KeyModifier modifiers)
    {
        for (auto* listener : m_mouseListeners)
        {
            listener->onMousePressed(button, modifiers);
        }
    }

    void Window::notifyMouseReleased(MouseButton button, KeyModifier modifiers)
    {
        for (auto* listener : m_mouseListeners)
        {
            listener->onMouseReleased(button, modifiers);
        }
    }

    void Window::windowClosedCallback(GLFWwindow* window)
    {
        Window* const	render = getWindowFromGLFWwindow(window);

        render->notifyWindowClosed();
    }

    void Window::windowMovedCallback(GLFWwindow* window, int x, int y)
    {
        Window* const	render = getWindowFromGLFWwindow(window);

        render->notifyWindowMoved(x, y);
    }

    void Window::windowResizedCallback(GLFWwindow* window, int width, int height)
    {
        Window* const	render = getWindowFromGLFWwindow(window);

        render->notifyWindowResized(width, height);
    }

    void Window::windowFocusCallback(GLFWwindow* window, int state)
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

    void Window::keyboardCallback(GLFWwindow* window, int key, int, int action, int modifiers)
    {
        Window* const	render = getWindowFromGLFWwindow(window);

        if (key == GLFW_KEY_UNKNOWN)
        {
            return;
        }
        switch (action)
        {
            case GLFW_PRESS:
                render->notifyKeyPressed(key, static_cast<KeyModifier>(modifiers));
                break;
            case GLFW_RELEASE:
                render->notifyKeyReleased(key, static_cast<KeyModifier>(modifiers));
                break;
            default:
                break;
        }
    }

    void Window::mouseMovedCallback(GLFWwindow* window, double x, double y)
    {
        Window* const	render = getWindowFromGLFWwindow(window);

        render->notifyMouseMoved(x, y);
    }

    void Window::mouseFocusCallback(GLFWwindow* window, int entered)
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

    void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
    {
        Window* const	render = getWindowFromGLFWwindow(window);

        switch(action)
        {
        case GLFW_PRESS:
            render->notifyMousePressed(static_cast<MouseButton>(button),
                                       static_cast<KeyModifier>(modifiers));
            break;
        case GLFW_RELEASE:
            render->notifyMouseReleased(static_cast<MouseButton>(button),
                                        static_cast<KeyModifier>(modifiers));
            break;
        default:
            break;
        }
    }

    void Window::WindowDeleter::operator()(GLFWwindow *window)
    {
        glfwDestroyWindow(window);
    }
}
