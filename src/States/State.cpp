/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** States / State.cpp
*/

#include "State.hpp"

////////////////////////////////////////////////////////////////////////////////

State::State()
: m_initialized(false)
, m_active(false)
, m_modal(true)
, m_fullscreen(true)
{
}

State::~State()
{
}

////////////////////////////////////////////////////////////////////////////////

void State::initialize()
{
	m_initialized = true;
}

void State::handleEvent(const sf::Event &e)
{
	m_events.dispatchEvent(e);

	for (auto &ui : m_gui)
		ui->handleEvent(e);
}

void State::update(const sf::Time &delta)
{
	onUpdate(delta);

	for (auto &ui : m_gui)
		ui->update(delta);
}

void State::staticUpdate(const sf::Time &delta)
{
	onStaticUpdate(delta);
}

void State::render(sf::RenderTarget &renderTarget)
{
	onRender(renderTarget);

	for (auto &ui : m_gui)
		ui->render(renderTarget);
}

void State::activate()
{
	m_active = true;
	onActivate();
}

void State::deactivate()
{
	m_active = false;
	onDeactivate();
}