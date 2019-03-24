/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** Test.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "GUI/Background.hpp"
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
		m_events.onKeyDown(std::bind(&Application::close, Application::instance()), sf::Keyboard::Q, EventListeners::Key::Ctrl);

		onInitialize.connect(this, &Test::initialize);
		onUpdate.connect(this, &Test::makeGUI);
	}

	~Test()
	{
		if (m_bg != nullptr)
			delete m_bg;
	}

public:
	void initialize() {
		m_bg = new GUI::Background();
		m_bg->setImage("tests/assets/beach.gif");
		onUpdate.connect(m_bg, &GUI::Background::update);
		onRender.connect((GUI::Widget *)m_bg, &GUI::Widget::render);
		m_events.onResize(std::bind(&GUI::Background::resize, m_bg, _1));
	}

	void makeGUI(const sf::Time &)
	{
		ImGui::ShowDemoWindow(NULL);

		// ImGui::Begin("Sample window");
		// 	if (ImGui::ColorEdit3("Background color", m_color)) {
		// 		std::cout << "color: " <<
		// 		(m_color[0] * 255.f) << "," <<
		// 		(m_color[1] * 255.f) << "," <<
		// 		(m_color[2] * 255.f) << std::endl;
		// 	}

		// 	ImGui::InputText("Window title", m_text, 255);

		// 	if (ImGui::Button("Update window title")) {
		// 		Application::instance()->window().title(std::string(m_text));
		// 	}
		// ImGui::End();
	}

private:
	GUI::Background *m_bg;

	// float m_color[3] = {0};
	// char m_text[255] = {0};
};

////////////////////////////////////////////////////////////////////////////////

}