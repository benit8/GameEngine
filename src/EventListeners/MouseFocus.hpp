/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** MouseFocus.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class MouseFocus;
}

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class MouseFocus : public IEventListener
{
public:
	typedef std::function<void()> Callback;

public:
	MouseFocus() {}
	~MouseFocus() override {}

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