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
	~Window() = default;

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

	Mode getMode() const;
	void setMode(Mode mode, const sf::Vector2u &size = sf::Vector2u(0, 0));
	const std::string &title() const;
	void title(const std::string &title);

	unsigned width() const;
	void width(int width);
	unsigned height() const;
	void height(int height);

	int top() const;
	void top(int top);
	int left() const;
	void left(int left);

	void setIcon(const std::string &path);
	void setCursor(sf::Cursor::Type type);

private:
	Mode m_mode;
	std::string m_title;
	sf::Vector2u m_startupSize;
};