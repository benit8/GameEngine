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

#include "States/State.hpp"

#include <exception>
#include <list>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

class StateManager
{
public:
	enum Flags
	{
		Push = 1 << 0,
		Pop  = 1 << 1,
		Swap = 1 << 2,
	};

public:
	StateManager();
	~StateManager();

public:
	template <typename T, typename... Args>
	void pushState(Args&&... args);
	template <typename T, typename... Args>
	void swapState(Args&&... args);

	void pushState(std::unique_ptr<State> state);
	void popState();
	void swapState(std::unique_ptr<State> state);

	State *getCurrentState() const;
	std::list<State *> getActiveStates();
	std::list<State *> getVisibleStates();

protected:
	void initializeStates();
	void updateStates();

private:
	std::list<std::unique_ptr<State>> m_states;
	std::unique_ptr<State> m_swap;
	int m_flags;
	bool m_active;
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