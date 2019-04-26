/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** States / State.cpp
*/

#include "State.hpp"

////////////////////////////////////////////////////////////////////////////////

State::State(const std::string &name)
: m_name(name)
, m_guiRoot(new GUI::Root)
{
	Logger::trace("States::%s: created", getName());
}

State::~State()
{
	Logger::trace("States::%s: destroyed", getName());
}

////////////////////////////////////////////////////////////////////////////////

void State::initialize()
{
	if (m_initialized)
		return;
	onInitialize();
	m_initialized = true;

	Logger::trace("States::%s: initialized", getName());
}

void State::handleEvent(const sf::Event &e)
{
	m_guiRoot->handleEvent(e);
	m_events.dispatchEvent(e);
}

void State::update(const sf::Time &delta)
{
	onUpdate(delta);
	m_guiRoot->update(delta);
}

void State::staticUpdate(const sf::Time &delta)
{
	onStaticUpdate(delta);
}

void State::render(sf::RenderTarget &renderTarget)
{
	onRender(renderTarget);
	m_guiRoot->render(renderTarget);
}

void State::activate()
{
	if (m_active)
		return;
	m_active = true;
	onActivate();

	Logger::trace("States::%s: activated", getName());
}

void State::deactivate()
{
	if (!m_active)
		return;
	m_active = false;
	onDeactivate();

	Logger::trace("States::%s: deactivated", getName());
}