/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** States / State.cpp
*/

#include "State.hpp"

////////////////////////////////////////////////////////////////////////////////

State::State()
{
}

State::~State()
{
}

////////////////////////////////////////////////////////////////////////////////

void State::initialize()
{
	if (m_initialized)
		return;
	m_initialized = true;

	onInitialize();
}

void State::handleEvent(const sf::Event &e)
{
	ImGui::SFML::ProcessEvent(e);

	m_events.dispatchEvent(e);
}

void State::update(const sf::Time &delta)
{
	onUpdate(delta);
}

void State::staticUpdate(const sf::Time &delta)
{
	onStaticUpdate(delta);
}

void State::render(sf::RenderTarget &renderTarget)
{
	onRender(renderTarget);
}

void State::activate()
{
	if (m_active)
		return;
	m_active = true;
	onActivate();
}

void State::deactivate()
{
	if (!m_active)
		return;
	m_active = false;
	onDeactivate();
}