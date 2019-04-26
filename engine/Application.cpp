/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "Logger.hpp"

////////////////////////////////////////////////////////////////////////////////

Application::Application()
: m_name("Application")
, m_shouldClose(false)
, m_fpsCounter(60)
{
}

Application::~Application()
{
	m_window.close();
}

////////////////////////////////////////////////////////////////////////////////

int Application::run()
{
	launch();

	sf::Time updateTimer = sf::Time::Zero;
	sf::Clock timer;
	while (running()) {
		sf::Time elapsed = timer.restart();
		updateTimer += elapsed;
		m_fpsCounter += elapsed;
		update(elapsed, false);

		bool shouldRender = false;
		while (updateTimer >= m_fpsCounter.getFrameTime()) {
			processEvents();
			update(elapsed, true);
			updateTimer -= m_fpsCounter.getFrameTime();
			shouldRender = true;
		}

		if (shouldRender) {
			m_window.clear();
			render();
			m_window.display();

			m_fpsCounter++;
		}

		updateStates();
	}

	Logger::warn("Application: shutting down");

	return EXIT_SUCCESS;
}

void Application::close()
{
	m_shouldClose = true;
}

////////////////////////////////////////////////////////////////////////////////

void Application::launch()
{
	Logger::info("Application: launching");

	if (!m_window.isOpen())
		m_window.open(m_name);

	initializeStates();
	m_fpsCounter.reset();
}

void Application::processEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e)) {
		switch (e.type) {
			case sf::Event::Closed:
				m_shouldClose = true;
				break;
			case sf::Event::Resized:
				m_window.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
				Logger::debug("Application: resized window to %ux%u", e.size.width, e.size.height);
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::F11) {
					if (m_window.getMode() == Window::Fullscreen)
						m_window.setMode(Window::Windowed);
					else
						m_window.setMode(Window::Fullscreen);
				}
				break;
			default:
				break;
		}

		// if (e.type == sf::Event::Closed || e.type == sf::Event::Resized)
		for (auto &state : getActiveStates())
			state->handleEvent(e);
		// getCurrentState()->handleEvent(e);
	}
}

void Application::update(const sf::Time &delta, bool staticUpdate)
{
	// auto subset = getActiveStates();
	for (auto &state : getActiveStates()) {
		if (staticUpdate)
			state->staticUpdate(delta);
		else
			state->update(delta);
	}
}

void Application::render()
{
	for (auto &state : getVisibleStates())
		state->render(m_window);

	m_fpsCounter.render(m_window);
}