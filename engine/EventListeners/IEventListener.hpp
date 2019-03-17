/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** IEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners {
	class IEventListener;
}

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <list>
#include <map>

#include <SFML/Window/Event.hpp>

////////////////////////////////////////////////////////////////////////////////

namespace EventListeners
{

class IEventListener
{
public:
	virtual ~IEventListener() {}

public:
	virtual void handleEvent(const sf::Event &) = 0;
};

}