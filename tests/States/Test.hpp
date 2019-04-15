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
	: State("Test")
	{
		m_events.onKeyDown(std::bind(&Application::close, Application::instance()), sf::Keyboard::Q, EventListeners::Key::Ctrl);

		onInitialize.connect(this, &Test::makeGUI);
	}

public:
	void makeGUI()
	{
		auto bg = makeGUIElement<GUI::Background>("bg");
		bg->setImage("tests/assets/beach.gif");

		m_input = makeGUIElement<GUI::Input>("input", "Type text here...");
		m_events.onResize([&](sf::Vector2u size) {
			m_input->setPosition((size.x - m_input->width()) / 2, (size.y - m_input->height()) / 2);
		});

		/*auto btn = */makeGUIElement<GUI::Button>("btn", "Click me nigger");
	}

private:
	std::shared_ptr<GUI::Input> m_input;
};

////////////////////////////////////////////////////////////////////////////////

}