/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** EventDispatcher.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class EventDispatcher;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <functional>
#include <map>

#include <SFML/Window/Event.hpp>

#include "EventListeners/Close.hpp"
#include "EventListeners/Resize.hpp"
#include "EventListeners/Focus.hpp"
#include "EventListeners/Text.hpp"
#include "EventListeners/Key.hpp"
#include "EventListeners/MouseWheel.hpp"
#include "EventListeners/MouseButton.hpp"
#include "EventListeners/MouseMove.hpp"
#include "EventListeners/MouseFocus.hpp"

////////////////////////////////////////////////////////////////////////////////

// Only for callbacks binding
using namespace std::placeholders;

#define BIND(C)  std::bind(&C, this)
#define BIND1(C) std::bind(&C, this, _1)
#define BIND2(C) std::bind(&C, this, _1, _2)
#define BIND3(C) std::bind(&C, this, _1, _2, _3)

////////////////////////////////////////////////////////////////////////////////

class EventDispatcher
{
public:
	EventDispatcher();
	~EventDispatcher();

public:
	void dispatchEvent(const sf::Event &e);

	void onClose(EventListeners::Close::Callback callback);
	void onResize(EventListeners::Resize::Callback callback);
	void onFocusIn(EventListeners::Focus::Callback callback);
	void onFocusOut(EventListeners::Focus::Callback callback);
	void onText(EventListeners::Text::Callback callback);
	void onKeyDown(EventListeners::Key::Callback callback, sf::Keyboard::Key key, EventListeners::Key::CtrlKey ctrlKeys = EventListeners::Key::None);
	void onKeyUp(EventListeners::Key::Callback callback, sf::Keyboard::Key key, EventListeners::Key::CtrlKey ctrlKeys = EventListeners::Key::None);
	void onMouseWheel(EventListeners::MouseWheel::Callback callback, sf::Mouse::Wheel wheel = sf::Mouse::VerticalWheel);
	void onMouseDown(EventListeners::MouseButton::Callback callback, sf::Mouse::Button button);
	void onMouseUp(EventListeners::MouseButton::Callback callback, sf::Mouse::Button button);
	void onMouseMove(EventListeners::MouseMove::Callback callback);
	void onMouseIn(EventListeners::MouseFocus::Callback callback);
	void onMouseOut(EventListeners::MouseFocus::Callback callback);

private:
	std::map<sf::Event::EventType, std::unique_ptr<EventListeners::IEventListener>> m_eventListeners;
};