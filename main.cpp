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

		m_events.onKeyDown([&]() {
			Application::getInstance()->close();
		}, sf::Keyboard::Escape);

		m_events.onKeyDown(BIND(TestState::switchScreen), sf::Keyboard::Space);

		onInitialize.connect(this, &TestState::initialize);
	}

	~TestState()
	{}

public:
	void initialize() {
		m_bg = makeGUI<GUI::Box>();
		if (!m_bg->setBackgroundImage("assets/bg.jpg"))
			std::cerr << "Failed to load image background" << std::endl;
	}

	void resized(sf::Vector2u size) {
		m_bg->setSize({size.x, size.y});
	}

	void switchScreen() {
		static bool windowed = true;

		if (windowed)
			Application::getInstance()->window().setMode(Window::Fullscreen);
		else
			Application::getInstance()->window().setMode(Window::Windowed, {1280, 720});

		windowed = !windowed;
	}

private:
	GUI::Box *m_bg = nullptr;
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