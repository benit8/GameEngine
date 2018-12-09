/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** EventDispatcher.cpp
*/

#include "EventDispatcher.hpp"

////////////////////////////////////////////////////////////////////////////////

EventDispatcher::EventDispatcher()
{
	m_eventListeners[sf::Event::Closed]              = std::make_unique<EventListeners::Close>();
	m_eventListeners[sf::Event::Resized]             = std::make_unique<EventListeners::Resize>();
	m_eventListeners[sf::Event::LostFocus]           = std::make_unique<EventListeners::Focus>();
	m_eventListeners[sf::Event::GainedFocus]         = std::make_unique<EventListeners::Focus>();
	m_eventListeners[sf::Event::TextEntered]         = std::make_unique<EventListeners::Text>();
	m_eventListeners[sf::Event::KeyPressed]          = std::make_unique<EventListeners::Key>();
	m_eventListeners[sf::Event::KeyReleased]         = std::make_unique<EventListeners::Key>();
	m_eventListeners[sf::Event::MouseWheelScrolled]  = std::make_unique<EventListeners::MouseWheel>();
	m_eventListeners[sf::Event::MouseButtonPressed]  = std::make_unique<EventListeners::MouseButton>();
	m_eventListeners[sf::Event::MouseButtonReleased] = std::make_unique<EventListeners::MouseButton>();
	m_eventListeners[sf::Event::MouseMoved]          = std::make_unique<EventListeners::MouseMove>();
	m_eventListeners[sf::Event::MouseEntered]        = std::make_unique<EventListeners::MouseFocus>();
	m_eventListeners[sf::Event::MouseLeft]           = std::make_unique<EventListeners::MouseFocus>();
}

EventDispatcher::~EventDispatcher()
{
}

////////////////////////////////////////////////////////////////////////////////

void EventDispatcher::dispatchEvent(const sf::Event &e)
{
	auto it = m_eventListeners.find(e.type);
	if (it != m_eventListeners.end())
		it->second->handleEvent(e);
}

////////////////////////////////////////////////////////////////////////////////

void EventDispatcher::onClose(EventListeners::Close::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::Closed);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::Close *>(it->second.get())->registerCallback(callback);
}

void EventDispatcher::onResize(EventListeners::Resize::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::Resized);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::Resize *>(it->second.get())->registerCallback(callback);
}

void EventDispatcher::onFocusIn(EventListeners::Focus::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::GainedFocus);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::Focus *>(it->second.get())->registerCallback(callback);
}

void EventDispatcher::onFocusOut(EventListeners::Focus::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::LostFocus);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::Focus *>(it->second.get())->registerCallback(callback);
}

void EventDispatcher::onText(EventListeners::Text::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::TextEntered);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::Text *>(it->second.get())->registerCallback(callback);
}

void EventDispatcher::onKeyDown(EventListeners::Key::Callback callback, sf::Keyboard::Key key, EventListeners::Key::CtrlKey ctrlKeys)
{
	auto it = m_eventListeners.find(sf::Event::KeyPressed);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::Key *>(it->second.get())->registerCallback(callback, key, ctrlKeys);
}

void EventDispatcher::onKeyUp(EventListeners::Key::Callback callback, sf::Keyboard::Key key, EventListeners::Key::CtrlKey ctrlKeys)
{
	auto it = m_eventListeners.find(sf::Event::KeyReleased);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::Key *>(it->second.get())->registerCallback(callback, key, ctrlKeys);
}

void EventDispatcher::onMouseWheel(EventListeners::MouseWheel::Callback callback, sf::Mouse::Wheel wheel)
{
	auto it = m_eventListeners.find(sf::Event::MouseWheelScrolled);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::MouseWheel *>(it->second.get())->registerCallback(callback, wheel);
}

void EventDispatcher::onMouseDown(EventListeners::MouseButton::Callback callback, sf::Mouse::Button button)
{
	auto it = m_eventListeners.find(sf::Event::MouseButtonPressed);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::MouseButton *>(it->second.get())->registerCallback(callback, button);
}

void EventDispatcher::onMouseUp(EventListeners::MouseButton::Callback callback, sf::Mouse::Button button)
{
	auto it = m_eventListeners.find(sf::Event::MouseButtonReleased);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::MouseButton *>(it->second.get())->registerCallback(callback, button);
}

void EventDispatcher::onMouseMove(EventListeners::MouseMove::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::MouseMoved);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::MouseMove *>(it->second.get())->registerCallback(callback);
}

void EventDispatcher::onMouseIn(EventListeners::MouseFocus::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::MouseEntered);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::MouseFocus *>(it->second.get())->registerCallback(callback);
}

void EventDispatcher::onMouseOut(EventListeners::MouseFocus::Callback callback)
{
	auto it = m_eventListeners.find(sf::Event::MouseLeft);
	if (it != m_eventListeners.end())
		dynamic_cast<EventListeners::MouseFocus *>(it->second.get())->registerCallback(callback);
}