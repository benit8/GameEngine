/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Close.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class Close;
}

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class Close : public IEventListener
{
public:
	typedef std::function<void()> Callback;

public:
	Close() {}
	~Close() override {}

public:
	void handleEvent(const sf::Event &) {
		for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			(*it)();
	}

	void registerCallback(Callback callback) {
		m_callbacks.push_back(callback);
	}

private:
	std::list<Callback> m_callbacks;
};

}