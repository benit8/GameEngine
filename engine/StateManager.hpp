/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** StateManager.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class StateManager;

////////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <list>
#include <memory>

#include "States/State.hpp"

////////////////////////////////////////////////////////////////////////////////

class StateManager
{
public:
	enum Flags
	{
		Pop	= (1 << 0),
		Swap	= (1 << 1),
	};

public:
	StateManager();
	~StateManager();

public:
	template <typename T, typename... Args>
	void pushState(Args&&... args);
	template <typename T, typename... Args>
	void swapState(Args&&... args);

	void pushState(State::Ptr state);
	void swapState(State::Ptr state);
	void popState();

	State *getCurrentState() const;
	std::list<State *> getActiveStates();
	std::list<State *> getVisibleStates();

protected:
	void updateStates();

private:
	std::list<State::Ptr> m_states;
	State::Ptr m_swap;
	int m_flags;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
inline void StateManager::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
inline void StateManager::swapState(Args&&... args)
{
	swapState(std::make_unique<T>(std::forward<Args>(args)...));
}