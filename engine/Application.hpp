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

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

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

	bool running() const { return !m_shouldClose && m_window.isOpen(); }
	void name(const std::string &name) { m_name = name; }
	const std::string &name() const { return m_name; }
	Window &window() { return m_window; }

private:
	Application();

	void launch();
	void processEvents();
	void update(const sf::Time &delta, bool staticUpdate);
	void render();

	friend Application *Singleton<Application>::instance();

private:
	std::string m_name;
	bool m_shouldClose;

	Window m_window;
	FPSCounter m_fpsCounter;
};