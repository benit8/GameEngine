/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** GUI / Root.cpp
*/

#include "Root.hpp"
#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Root::Root()
: m_id("_root")
{
}

////////////////////////////////////////////////////////////////////////////////

void Root::handleEvent(const sf::Event &e)
{
	// To be set true when a widget is clicked
	if (e.type == sf::Event::MouseButtonPressed)
		Env::foundTarget = false;

	for (auto &c : getChildren())
		c->handleEvent(e);

	// When a widget is focused and we clicked on nothing, unfocus it
	if (e.type == sf::Event::MouseButtonPressed && (!Env::foundTarget && Env::target != nullptr)) {
		Env::target->unfocus();
		Env::target = nullptr;
	}
}

void Root::update(const sf::Time &delta)
{
	for (auto &c : getChildren())
		c->doUpdate(delta);
}

void Root::render(sf::RenderTarget &rt)
{
	for (auto &c : getChildren())
		c->doRender(rt);
}

////////////////////////////////////////////////////////////////////////////////

}