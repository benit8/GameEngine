/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Text.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class Text;
}

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class Text : public IEventListener
{
public:
	typedef std::function<void(unsigned)> Callback;

public:
	Text() {}
	~Text() override {}

public:
	void handleEvent(const sf::Event &e) {
		for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			(*it)(e.text.unicode);
	}

	void registerCallback(Callback callback) {
		m_callbacks.push_back(callback);
	}

private:
	std::list<Callback> m_callbacks;
};

}