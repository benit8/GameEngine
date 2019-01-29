/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** States / State.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class State;

////////////////////////////////////////////////////////////////////////////////

#include "EventDispatcher.hpp"
#include "../Utils/Signal.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

////////////////////////////////////////////////////////////////////////////////

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

public:
	State();
	virtual ~State();

public:
	void initialize();
	void handleEvent(const sf::Event &e);
	void update(const sf::Time &delta);
	void staticUpdate(const sf::Time &delta);
	void render(sf::RenderTarget &renderTarget);

	void activate();
	void deactivate();

	bool isInitialized() const { return m_initialized; }
	bool isActive() const { return m_active; }
	bool isModal() const { return m_modal; }
	void setModal(bool _) { m_modal = _; }
	bool isFullscreen() const { return m_fullscreen; }
	void setFullscreen(bool _) { m_fullscreen = _; }

	Signal<> onActivate;
	Signal<> onDeactivate;
	Signal<> onInitialize;
	Signal<const sf::Time &> onUpdate;
	Signal<const sf::Time &> onStaticUpdate;
	Signal<sf::RenderTarget &> onRender;

protected:
	EventDispatcher m_events;

	bool m_initialized = false;
	bool m_active = false;
	bool m_modal = true;
	bool m_fullscreen = true;
};