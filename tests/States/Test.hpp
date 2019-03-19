/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** Test.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "States/State.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

////////////////////////////////////////////////////////////////////////////////

class Test : public State
{
public:
	Test()
	{
		m_events.onResize(BIND1(Test::resized));
		m_events.onKeyDown(BIND(Test::switchFullscreen), sf::Keyboard::F11);
		m_events.onKeyDown([&]() { Application::get()->close(); }, sf::Keyboard::Escape);

		// onInitialize.connect(this, &Test::initialize);
		onUpdate.connect(this, &Test::makeGUI);
	}

	~Test()
	{}

public:
	void initialize() {
		// m_bg = makeGUI<GUI::Box>();
		// m_bg->setBackgroundImage("assets/waterfall.gif");
		// m_bg->setBackgroundImage("assets/beach.gif");
	}

	void resized(sf::Vector2u size) {
		// m_bg->setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
	}

	void switchFullscreen() {
		static bool fullscreen = false;
		if (!fullscreen) Application::get()->window().setMode(Window::Fullscreen);
		else             Application::get()->window().setMode(Window::Windowed);
		fullscreen = !fullscreen;
	}

	void makeGUI(const sf::Time &/*delta*/)
	{
		/* ImGui::Begin("Sample window");

		if (ImGui::ColorEdit3("Background color", m_color)) {
			std::cout << "color: " <<
			(m_color[0] * 255.f) << "," <<
			(m_color[1] * 255.f) << "," <<
			(m_color[2] * 255.f) << std::endl;
		}

		ImGui::InputText("Window title", m_text, 255);

		if (ImGui::Button("Update window title")) {
			std::cout << m_text << std::endl;
		}

		ImGui::End(); */
		ImGui::ShowDemoWindow(NULL);
	}

private:
	// GUI::Box *m_bg = nullptr;

	float m_color[3] = {0};
	char m_text[255] = {0};
};

////////////////////////////////////////////////////////////////////////////////

}