/*
** EPITECH PROJECT, 2018
** Netiles
** File description:
** Window.cpp
*/

#include "Window.hpp"

////////////////////////////////////////////////////////////////////////////////

Window::Window()
: sf::RenderWindow()
, m_mode(Windowed)
, m_title("")
, m_startupSize(600, 800)
{
}

Window::Window(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, const sf::ContextSettings &settings)
: sf::RenderWindow(videoMode, title, styles, settings)
, m_mode(Windowed)
, m_title("")
, m_startupSize(600, 800)
{
}

////////////////////////////////////////////////////////////////////////////////

void Window::create(const std::string &title, int)
{
	create(title, m_startupSize);
}

void Window::create(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, const sf::ContextSettings &settings)
{
	sf::RenderWindow::create(videoMode, title, styles, settings);
}

void Window::create(const std::string &title, const sf::Vector2u &windowSize, sf::Uint32 styles, const sf::ContextSettings &settings)
{
	create(title, sf::VideoMode(windowSize.x, windowSize.y), styles, settings);
}

void Window::createBorderless(const std::string &title)
{
	create(title, sf::VideoMode::getFullscreenModes()[0], sf::Style::None);
}

void Window::createFullscreen(const std::string &title)
{
	create(title, sf::VideoMode::getFullscreenModes()[0], sf::Style::Fullscreen);
}


Window::Mode Window::getMode() const
{
	return m_mode;
}

void Window::setMode(Mode mode, const sf::Vector2u &size)
{
	sf::Vector2u currentSize = getSize();

	if (isOpen()) {
		switch (mode) {
			case Windowed:
				if (size != currentSize)
					setSize(size);
				else
					create(title(), sf::VideoMode(size.x, size.y));
				break;
			case Borderless:
				if (m_mode != Borderless)
					createBorderless(title());
				break;
			case Fullscreen:
				if (m_mode != Fullscreen)
					createFullscreen(title());
				break;
		}
	}
	else if (size.x != 0 && size.y != 0) {
		m_startupSize = size;
	}

	m_mode = mode;
}

const std::string &Window::title() const
{
	return m_title;
}

void Window::title(const std::string &title)
{
	m_title = title;
	setTitle(title);
}


unsigned Window::width() const
{
	return getSize().x;
}

void Window::width(int width)
{
	setSize(sf::Vector2u(width, height()));
}

unsigned Window::height() const
{
	return getSize().y;
}

void Window::height(int height)
{
	setSize(sf::Vector2u(width(), height));
}


int Window::left() const
{
	return getPosition().y;
}

void Window::left(int left)
{
	setPosition(sf::Vector2i(top(), left));
}

int Window::top() const
{
	return getPosition().y;
}

void Window::top(int top)
{
	setPosition(sf::Vector2i(top, left()));
}


void Window::setIcon(const std::string &path)
{
	sf::Image icon;

	if (!icon.loadFromFile(path)) {
		std::cerr << "Could not open '" << path << "' for window icon" << std::endl;
		return;
	}

	sf::Vector2u size = icon.getSize();
	sf::RenderWindow::setIcon(size.x, size.y, icon.getPixelsPtr());
}

void Window::setCursor(sf::Cursor::Type type)
{
	sf::Cursor cursor;

	if (cursor.loadFromSystem(type))
		setMouseCursor(cursor);
}