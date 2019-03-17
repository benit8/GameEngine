/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Resize.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class Resize;
}

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class Resize : public IEventListener
{
public:
	typedef std::function<void(sf::Vector2u)> Callback;

public:
	Resize() {}
	~Resize() override {}

public:
	void handleEvent(const sf::Event &e) {
		sf::Vector2u size(e.size.width, e.size.height);
		for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			(*it)(size);
	}

	void registerCallback(Callback callback) {
		m_callbacks.push_back(callback);
	}

private:
	std::list<Callback> m_callbacks;
};

}