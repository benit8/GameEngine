/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** GUI / Root.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Root;
}

////////////////////////////////////////////////////////////////////////////////

#include "Parent.hpp"

#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Root : public Parent
{
public:
	Root();

	void handleEvent(const sf::Event &e);
	void update(const sf::Time &delta);
	void render(sf::RenderTarget &rt);

	Root *getRoot() override { return this; }
	const Root *getRoot() const override { return this; }
	const std::string &getId() const override { return m_id; }

private:
	std::string m_id;
};

}