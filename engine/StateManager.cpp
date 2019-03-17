/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** StateManager.cpp
*/

#include "StateManager.hpp"

////////////////////////////////////////////////////////////////////////////////

StateManager::StateManager()
: m_swap(nullptr)
, m_flags(0)
{
}

StateManager::~StateManager()
{
	m_states.clear();
}

////////////////////////////////////////////////////////////////////////////////

void StateManager::pushState(State::Ptr state)
{
	if (!state->isInitialized())
		state->initialize();
	state->activate();
	m_states.push_back(std::move(state));
}

void StateManager::swapState(State::Ptr state)
{
	if (!state->isInitialized())
		state->initialize();
	state->activate();
	m_swap = std::move(state);
	m_flags |= Pop | Swap;
}

void StateManager::popState()
{
	m_flags |= Pop;
}

////////////////////////////////////////////////////////////////////////////////

void StateManager::updateStates()
{
	if (m_flags & Pop) {
		m_states.back()->deactivate();
		m_states.pop_back();
		m_flags &= ~Pop;

		if (m_flags & Swap) {
			m_flags &= ~Swap;
			m_states.push_back(std::move(m_swap));
			m_swap = nullptr;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

State *StateManager::getCurrentState() const
{
	if (m_states.empty())
		throw std::logic_error("StateManager is empty");

	return m_states.back().get();
}

std::list<State *> StateManager::getActiveStates()
{
	std::list<State *> activeStates;

	if (m_states.empty())
		return activeStates;

	auto it = m_states.end();
	do {
		--it;
	} while (it != m_states.begin() && !(*it)->isFullscreen());

	for (; it != m_states.end(); ++it)
		activeStates.push_back(it->get());

	return activeStates;
}

std::list<State *> StateManager::getVisibleStates()
{
	std::list<State *> visibleStates;

	auto it = m_states.rbegin();
	for (; it != m_states.rend(); ++it) {
		auto state = it->get();
		if (!state->isActive())
			state->activate();
		visibleStates.push_back(state);
		if (state->isModal() || state->isFullscreen()) {
			++it;
			break;
		}
	}

	for (; it != m_states.rend(); ++it) {
		auto state = it->get();
		if (state->isActive())
			state->deactivate();
	}

	return visibleStates;
}