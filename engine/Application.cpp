/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Application.cpp
*/

#include "Application.hpp"

////////////////////////////////////////////////////////////////////////////////

Application::Application()
: m_name("Application")
, m_shouldClose(false)
{
	m_fpsCounter.setLimit(60);
}

Application::~Application()
{
	m_window.close();
	ImGui::SFML::Shutdown();
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
	if (!m_window.isOpen())
		m_window.open(m_name);

	ImGui::SFML::Init(m_window);

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

		for (auto &state : getActiveStates())
			state->handleEvent(e);
	}
}

void Application::update(const sf::Time &delta, bool staticUpdate)
{
	for (auto &state : getActiveStates()) {
		if (staticUpdate)
			state->staticUpdate(delta);
		else {
			ImGui::SFML::Update(m_window, delta);
			state->update(delta);
			ImGui::EndFrame();
		}
	}
}

void Application::render()
{
	for (auto &state : getVisibleStates())
		state->render(m_window);

	ImGui::SFML::Render(m_window);

	m_fpsCounter.render(m_window);
}