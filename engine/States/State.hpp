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
	State(const std::string &name = "<unnamed state>");
	~State();

public:
	void initialize();
	void handleEvent(const sf::Event &e);
	void update(const sf::Time &delta, sf::RenderWindow &window, bool updateGui = true);
	void staticUpdate(const sf::Time &delta);
	void render(sf::RenderTarget &renderTarget);

	void activate();
	void deactivate();

	void setModal(bool m) { m_modal = m; }
	void setFullscreen(bool f) { m_fullscreen = f; }

	bool isInitialized() const { return m_initialized; }
	bool isActive() const { return m_active; }
	bool isModal() const { return m_modal; }
	bool isFullscreen() const { return m_fullscreen; }

	const std::string &getName() { return m_name; }

	Signal<> onActivate;
	Signal<> onDeactivate;
	Signal<> onInitialize;
	Signal<const sf::Time &> onUpdate;
	Signal<const sf::Time &> onStaticUpdate;
	Signal<sf::RenderTarget &> onRender;

protected:
	std::string m_name;
	EventDispatcher m_events;
	ImGuiContext *m_guiContext;

	bool m_initialized = false;
	bool m_active = false;
	bool m_modal = true; // Prevents all states before this one to call `update()` methods
	bool m_fullscreen = true; // Prevents all states before this one to call `render()`
};