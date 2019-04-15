/*
** EPITECH PROJECT, 2018
** Netiles
** File description:
** Window.cpp
*/

#include "Window.hpp"

#include <map>

////////////////////////////////////////////////////////////////////////////////

Window::Window()
: sf::RenderWindow()
, m_mode(Undefined)
, m_title("")
, m_startupSize(getDefaultSize())
{
}

Window::Window(const std::string &title, Mode mode, sf::Vector2u size)
: sf::RenderWindow(sf::VideoMode(size.x, size.y), title, styleFromMode(mode), sf::ContextSettings(24, 8, 0, 3, 0))
, m_mode(mode)
, m_title(title)
, m_startupSize(size)
{
}

////////////////////////////////////////////////////////////////////////////////

void Window::open(const std::string &title, Mode mode, sf::Vector2u size)
{
	if (mode == Undefined && m_mode != Undefined)
		mode = m_mode;
	if (size.x == 0 || size.y == 0)
		size = m_startupSize;

	openSF(title, sf::VideoMode(size.x, size.y), styleFromMode(mode));
	m_mode = mode;
}

void Window::openWindowed(sf::Vector2u size)
{
	if (size.x == 0 || size.y == 0)
		size = m_startupSize;
	openSF(title(), sf::VideoMode(size.x, size.y), sf::Style::Default);
}

void Window::openBorderless()
{
	openSF(title(), sf::VideoMode::getFullscreenModes()[0], sf::Style::None);
}

void Window::openFullscreen()
{
	openSF(title(), sf::VideoMode::getFullscreenModes()[0], sf::Style::Fullscreen);
}


void Window::setMode(Mode mode, sf::Vector2u size)
{
	if (mode == Undefined)
		mode = Windowed;
	if (size.x == 0 || size.y == 0)
		size = getDefaultSize();

	if (!isOpen()) {
		m_mode = mode;
		m_startupSize = size;
	}
	else {
		if (mode == m_mode) {
			if (mode == Windowed && size != getSize())
				setSize(size);
			return;
		}

		switch (mode) {
			default:
			case Windowed:   openWindowed(size); break;
			case Borderless: openBorderless();   break;
			case Fullscreen: openFullscreen();   break;
		}
	}
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

////////////////////////////////////////////////////////////////////////////////

void Window::openSF(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, const sf::ContextSettings &settings)
{
	create(videoMode, title, styles, settings);
	m_mode = modeFromStyle(styles);
}

////////////////////////////////////////////////////////////////////////////////

sf::Uint32 Window::styleFromMode(Mode &mode)
{
	static std::map<Mode, sf::Uint32> modes = {
		{Windowed, sf::Style::Default},
		{Borderless, sf::Style::None},
		{Fullscreen, sf::Style::Fullscreen}
	};

	if (mode == Undefined)
		mode = Windowed;

	return modes[mode];
}

Window::Mode Window::modeFromStyle(sf::Uint32 style)
{
	if (style & sf::Style::Fullscreen)
		return Fullscreen;
	else if ((style & sf::Style::Titlebar) || (style & sf::Style::Resize) || (style & sf::Style::Close))
		return Windowed;
	else
		return Borderless;
}

sf::Vector2u Window::getDefaultSize()
{
	auto dm = sf::VideoMode::getDesktopMode();
	return sf::Vector2u(dm.width, dm.height);
}