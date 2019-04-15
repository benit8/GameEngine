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

#include "StateManager.hpp"
#include "Graphics/FPSCounter.hpp"
#include "Graphics/Window.hpp"
#include "Utils/Singleton.hpp"

#include <string>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

////////////////////////////////////////////////////////////////////////////////

class Application : public Singleton<Application>, public StateManager
{
public:
	~Application();

	int run();
	void close();

	bool running() const { return !m_shouldClose && m_window.isOpen(); }
	void name(const std::string &name) { m_name = name; }
	const std::string &name() const { return m_name; }
	Window &window() { return m_window; }
	void args(int argc, char **argv) { m_binName = argv[0]; m_args.assign(argv + 1, argv + argc); }
	const std::vector<std::string> &args() { return m_args; }

private:
	Application();

	void launch();
	void processEvents();
	void update(const sf::Time &delta, bool staticUpdate);
	void render();

	friend Application *Singleton<Application>::instance();

private:
	std::string m_name;
	std::string m_binName;
	std::vector<std::string> m_args;
	bool m_shouldClose;

	Window m_window;
	FPSCounter m_fpsCounter;
};