/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Window.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Window;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

////////////////////////////////////////////////////////////////////////////////

class Window : public sf::RenderWindow
{
public:
	enum Mode
	{
		Windowed,
		Borderless,
		Fullscreen
	};

public:
	Window();
	Window(const std::string &title,
	       sf::VideoMode videoMode = sf::VideoMode::getDesktopMode(),
	       sf::Uint32 styles = sf::Style::Default,
	       const sf::ContextSettings &settings = sf::ContextSettings(24, 8, 0, 3, 0));
	~Window();

public:
	void open(const std::string &title,
	          sf::VideoMode videoMode = sf::VideoMode::getDesktopMode(),
	          sf::Uint32 styles = sf::Style::Default,
	          const sf::ContextSettings &settings = sf::ContextSettings(24, 8, 0, 3, 0));
	void open(const std::string &title,
	          sf::Vector2u windowSize,
	          sf::Uint32 styles = sf::Style::Default,
	          const sf::ContextSettings &settings = sf::ContextSettings(24, 8, 0, 3, 0));
	void openBorderless(const std::string &title);
	void openFullscreen(const std::string &title);

	void setMode(Mode mode, const sf::Vector2u &size = sf::Vector2u(0, 0));
	Mode getMode() const { return m_mode; }

	const std::string &title() const { return m_title; }
	void title(const std::string &title) { m_title = title; setTitle(title); }

	unsigned width() const { return getSize().x; }
	void width(int width) { setSize(sf::Vector2u(width, height())); }
	unsigned height() const { return getSize().y; }
	void height(int height) { setSize(sf::Vector2u(width(), height)); }

	int top() const { return getPosition().y; }
	void top(int top) { setPosition(sf::Vector2i(top, left())); }
	int left() const { return getPosition().x; }
	void left(int left) { setPosition(sf::Vector2i(top(), left)); }

	void setIcon(const std::string &path);
	void setCursor(sf::Cursor::Type type);

private:
	Mode m_mode;
	std::string m_title;
	sf::Vector2u m_startupSize;
};