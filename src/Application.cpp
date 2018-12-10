/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Application.cpp
*/

#include "Application.hpp"

////////////////////////////////////////////////////////////////////////////////

Application::Application()
: m_appName("Application")
, m_shouldClose(false)
{
	m_fpsCounter.setLimit(60);
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
		m_fpsCounter.addFrameTime(elapsed);
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

			m_fpsCounter.incrementFrameCount();
		}

		updateStates();
	}

	return EXIT_SUCCESS;
}

void Application::close()
{
	m_shouldClose = true;
}

////////////////////////////////////////////////////////////////////////////////

void Application::launch()
{
	m_window.create(m_appName, 0);
	m_fpsCounter.reset();
}

void Application::processEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e)) {
		for (auto &state : getActiveStates())
			state->handleEvent(e);

		switch (e.type) {
			case sf::Event::Closed:
				m_shouldClose = true;
				break;
			case sf::Event::Resized:
				m_window.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
				break;
			default:
				break;
		}
	}
}

void Application::update(const sf::Time &delta, bool staticUpdate)
{
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