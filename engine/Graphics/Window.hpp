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
		Undefined = -1,
		Windowed,
		Borderless,
		Fullscreen
	};

public:
	// Instanciate without opening the window
	Window();
	// Instanciate and open the window
	Window(const std::string &title, Mode mode, sf::Vector2u size);

public:
	void open(const std::string &title, Mode mode = Undefined, sf::Vector2u size = {0, 0});

private:
	void openWindowed(sf::Vector2u size = {0, 0});
	void openBorderless();
	void openFullscreen();

public:
	void setMode(Mode mode, sf::Vector2u size = {0, 0});
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

	static sf::Uint32 styleFromMode(Mode &mode);
	static Mode modeFromStyle(sf::Uint32 style);
	static sf::Vector2u getDefaultSize();

private:
	void openSF(const std::string &title,
	            sf::VideoMode videoMode = sf::VideoMode::getDesktopMode(),
	            sf::Uint32 styles = sf::Style::Default,
	            const sf::ContextSettings &settings = sf::ContextSettings(24, 8, 0, 3, 0));

private:
	Mode m_mode;
	std::string m_title;
	sf::Vector2u m_startupSize;
};