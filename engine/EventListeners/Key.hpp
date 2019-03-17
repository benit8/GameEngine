/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Key.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class Key;
}

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

#include <type_traits>

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class Key : public IEventListener
{
public:
	enum CtrlKey
	{
		None	= 0,
		Ctrl	= (1 << 0),
		Shift	= (1 << 1),
		Alt	= (1 << 2),
		System	= (1 << 3)
	};

	typedef std::function<void()> Callback;

public:
	Key() {}
	~Key() override {}

public:
	void handleEvent(const sf::Event &e) override
	{
		auto key = keyFromEvent(e.key);
		auto it = m_callbacks.find(key);
		if (it != m_callbacks.end()) {
			for (auto it = m_callbacks[key].begin(); it != m_callbacks[key].end(); ++it)
				(*it)();
		}
	}

	void registerCallback(Callback callback, sf::Keyboard::Key key, CtrlKey ctrlKeys = CtrlKey::None) {
		m_callbacks[std::make_pair(key, ctrlKeys)].push_back(callback);
	}

private:
	std::pair<sf::Keyboard::Key, CtrlKey> keyFromEvent(const sf::Event::KeyEvent &e)
	{
		int ctrlMask = 0;
		if (e.control) ctrlMask |= static_cast<int>(CtrlKey::Ctrl);
		if (e.shift)   ctrlMask |= static_cast<int>(CtrlKey::Shift);
		if (e.alt)     ctrlMask |= static_cast<int>(CtrlKey::Alt);
		if (e.system)  ctrlMask |= static_cast<int>(CtrlKey::System);

		return std::make_pair(e.code, static_cast<CtrlKey>(ctrlMask));
	}

private:
	std::map<std::pair<sf::Keyboard::Key, CtrlKey>, std::list<Callback>> m_callbacks;
};

}