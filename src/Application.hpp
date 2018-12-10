/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Application.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Application;

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "StateManager.hpp"
#include "Graphics/FPSCounter.hpp"
#include "Graphics/Window.hpp"
#include "Utils/Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////

class Application : public StateManager, public Singleton<Application>
{
public:
	~Application();

	int run();
	void close();

	bool running() const { return !m_shouldClose; }
	void appName(const std::string &name) { m_appName = name; }
	const std::string &appName() const { return m_appName; }
	Window &window() { return m_window; }

private:
	Application();

	void launch();
	void processEvents();
	void update(const sf::Time &delta, bool staticUpdate);
	void render();

	friend Application *Singleton<Application>::getInstance();

private:
	std::string m_appName;
	bool m_shouldClose;

	Window m_window;

	FPSCounter m_fpsCounter;
};