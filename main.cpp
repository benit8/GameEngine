/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Core / tests / main.cpp
*/

#include "Application.hpp"
#include "States/State.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState()
	: State()
	{
		m_events.onClose()
	}

	~TestState()
	{}

public:
	void initialize() override {
		State::initialize();

		makeGUI<GUI::Box>();
	}
	void staticUpdate(const sf::Time &) {}
	void update(const sf::Time &) {}
	void render(sf::RenderTarget &) {}
};

////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	Application *app = Application::getInstance();
	app->appName("Engine");
	app->window().setMode(Window::Windowed, {1280, 720});
	app->pushState<TestState>();

	return app->run();
}