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
	{
		m_events.onResize(BIND1(TestState::resized));

		m_events.onKeyDown([&]() { Application::getInstance()->close(); }, sf::Keyboard::Escape);
		m_events.onKeyDown(BIND(TestState::switchFullscreen), sf::Keyboard::F11);

		onInitialize.connect(this, &TestState::initialize);
	}

	~TestState()
	{}

public:
	void initialize() {
		m_bg = makeGUI<GUI::Box>();
		m_bg->setBackgroundImage("assets/waterfall.gif");
	}

	void resized(sf::Vector2u size) {
		m_bg->setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
	}

	void switchFullscreen() {
		static bool fullscreen = false;
		if (!fullscreen) Application::getInstance()->window().setMode(Window::Fullscreen);
		else             Application::getInstance()->window().setMode(Window::Windowed);
		fullscreen = !fullscreen;
	}

private:
	GUI::Box *m_bg = nullptr;
};

////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	Application *app = Application::getInstance();
	app->appName("Engine");
	app->window().setMode(Window::Windowed/*, {1280, 720}*/);
	app->pushState<TestState>();

	return app->run();
}