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
, m_startupSize(800, 600)
{
	auto dm = sf::VideoMode::getDesktopMode();
	m_startupSize.x = dm.width;
	m_startupSize.y = dm.height;
}

Window::Window(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, const sf::ContextSettings &settings)
: sf::RenderWindow(videoMode, title, styles, settings)
, m_mode(Windowed)
, m_title("")
, m_startupSize(800, 600)
{
	auto dm = sf::VideoMode::getDesktopMode();
	m_startupSize.x = dm.width;
	m_startupSize.y = dm.height;
}

Window::~Window()
{
}

////////////////////////////////////////////////////////////////////////////////

void Window::open(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, const sf::ContextSettings &settings)
{
	create(videoMode, title, styles, settings);
}

void Window::open(const std::string &title, sf::Vector2u windowSize, sf::Uint32 styles, const sf::ContextSettings &settings)
{
	if (windowSize.x == 0 && windowSize.y == 0)
		windowSize = m_startupSize;
	open(title, sf::VideoMode(windowSize.x, windowSize.y), styles, settings);
}

void Window::openBorderless(const std::string &title)
{
	open(title, sf::VideoMode::getFullscreenModes()[0], sf::Style::None);
}

void Window::openFullscreen(const std::string &title)
{
	open(title, sf::VideoMode::getFullscreenModes()[0], sf::Style::Fullscreen);
}


void Window::setMode(Mode mode, const sf::Vector2u &_size)
{
	sf::Vector2u size = (_size.x == 0 || _size.y == 0) ? m_startupSize : _size;
	sf::Vector2u currentSize = getSize();

	if (isOpen()) {
		switch (mode) {
			case Windowed:
				if (mode == m_mode && size != currentSize)
					setSize(size);
				else
					open(title(), sf::VideoMode(size.x, size.y));
				break;
			case Borderless:
				if (m_mode != Borderless)
					openBorderless(title());
				break;
			case Fullscreen:
				if (m_mode != Fullscreen)
					openFullscreen(title());
				break;
		}
	}
	else {
		m_startupSize = size;
	}

	m_mode = mode;
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