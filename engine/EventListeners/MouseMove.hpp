/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** MouseMove.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class MouseMove;
}

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class MouseMove : public IEventListener
{
public:
	typedef std::function<void(sf::Vector2i, sf::Vector2i)> Callback;

public:
	MouseMove() : m_lastPos(0, 0) {}
	~MouseMove() override {}

public:
	void handleEvent(const sf::Event &e) override
	{
		sf::Vector2i pos(e.mouseMove.x, e.mouseMove.y);

		for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			(*it)(pos, pos - m_lastPos);

		m_lastPos = pos;
	}

	void registerCallback(Callback callback) {
		m_callbacks.push_back(callback);
	}

private:
	std::list<Callback> m_callbacks;
	sf::Vector2i m_lastPos;
};

}