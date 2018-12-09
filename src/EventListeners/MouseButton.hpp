/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** MouseButton.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class MouseButton;
}

////////////////////////////////////////////////////////////////////////////////

#include <SFML/System/Vector2.hpp>

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class MouseButton : public IEventListener
{
public:
	typedef std::function<void(sf::Vector2i)> Callback;

public:
	MouseButton() {}
	~MouseButton() override {}

public:
	void handleEvent(const sf::Event &e) override
	{
		sf::Mouse::Button btn = e.mouseButton.button;
		if (m_callbacks.find(btn) == m_callbacks.end())
			return;

		sf::Vector2i pos(e.mouseButton.x, e.mouseButton.y);
		for (auto it = m_callbacks[btn].begin(); it != m_callbacks[btn].end(); ++it)
			(*it)(pos);
	}

	void registerCallback(Callback callback, sf::Mouse::Button button) {
		m_callbacks[button].push_back(callback);
	}

private:
	std::map<sf::Mouse::Button, std::list<Callback>> m_callbacks;
};

}