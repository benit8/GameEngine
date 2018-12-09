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
#include "GUI/GUI.hpp"

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
	virtual void initialize();
	virtual void handleEvent(const sf::Event &e);
	virtual void update(const sf::Time &delta);
	virtual void staticUpdate(const sf::Time &delta);
	virtual void render(sf::RenderTarget &renderTarget);

	virtual void activate();
	virtual void deactivate();

	template <class T, class ...Args>
	T *makeGUI(Args&&... args)
	{
		T *ptr = new T(std::forward<Args>(args)...);
		m_gui.emplace_back(ptr);
		return ptr;
	}

	bool isInitialized() const { return m_initialized; }
	bool isActive() const { return m_active; }
	bool isModal() const { return m_modal; }
	void setModal(bool _) { m_modal = _; }
	bool isFullscreen() const { return m_fullscreen; }
	void setFullscreen(bool _) { m_fullscreen = _; }

	Signal<> onActivate;
	Signal<> onDeactivate;
	Signal<const sf::Time &> onUpdate;
	Signal<const sf::Time &> onStaticUpdate;
	Signal<sf::RenderTarget &> onRender;

protected:
	EventDispatcher m_events;
	std::list<std::unique_ptr<GUI::Widget>> m_gui;

	bool m_initialized;
	bool m_active;
	bool m_modal;
	bool m_fullscreen;
};