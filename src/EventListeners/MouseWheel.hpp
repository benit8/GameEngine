/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** MouseWheel.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class MouseWheel;
}

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class MouseWheel : public IEventListener
{
public:
	typedef std::function<void(float, sf::Vector2i)> Callback;

public:
	MouseWheel() {}
	~MouseWheel() override {}

public:
	void handleEvent(const sf::Event &e) {
		sf::Event::MouseWheelScrollEvent data = e.mouseWheelScroll;
		if (m_callbacks.find(data.wheel) == m_callbacks.end())
			return;

		for (auto it = m_callbacks[data.wheel].begin(); it != m_callbacks[data.wheel].end(); ++it)
			(*it)(data.delta, sf::Vector2i(data.x, data.y));
	}

	void registerCallback(Callback callback, sf::Mouse::Wheel wheel) {
		m_callbacks[wheel].push_back(callback);
	}

private:
	std::map<sf::Mouse::Wheel, std::list<Callback>> m_callbacks;
};

}