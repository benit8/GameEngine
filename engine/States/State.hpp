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

#include "../EventDispatcher.hpp"
#include "../Logger.hpp"
#include "../Utils/Signal.hpp"
#include "../GUI/GUI.hpp"

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
	void update(const sf::Time &delta);
	void staticUpdate(const sf::Time &delta);
	void render(sf::RenderTarget &renderTarget);

	const std::string &getName() { return m_name; }

	void activate();
	void deactivate();

	void setModal(bool m) { m_modal = m; }
	void setFullscreen(bool f) { m_fullscreen = f; }

	bool isInitialized() const { return m_initialized; }
	bool isActive() const { return m_active; }
	bool isModal() const { return m_modal; }
	bool isFullscreen() const { return m_fullscreen; }

	template <typename T, typename... Args>
	std::shared_ptr<T> makeGUIElement(Args&&... args) { return m_guiRoot->makeChild<T>(std::forward<Args>(args)...); }

	Signal<> onActivate;
	Signal<> onDeactivate;
	Signal<> onInitialize;
	Signal<const sf::Time &> onUpdate;
	Signal<const sf::Time &> onStaticUpdate;
	Signal<sf::RenderTarget &> onRender;

protected:
	std::string m_name;
	EventDispatcher m_events;

	bool m_initialized = false;
	bool m_active = false;
	bool m_modal = true; // Prevents all states before this one to call `update()` methods
	bool m_fullscreen = true; // Prevents all states before this one to call `render()`

private:
	std::unique_ptr<GUI::Root> m_guiRoot = nullptr;
};