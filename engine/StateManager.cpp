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
, m_active(false)
{
}

StateManager::~StateManager()
{
	m_states.clear();
}

////////////////////////////////////////////////////////////////////////////////

void StateManager::pushState(std::unique_ptr<State> state)
{
	if (m_active && !state->isInitialized())
		state->initialize();

	m_states.push_back(std::move(state));
}

void StateManager::swapState(std::unique_ptr<State> state)
{
	if (m_active && !state->isInitialized())
		state->initialize();

	m_swap = std::move(state);
	m_flags |= Pop | Swap;
}

void StateManager::popState()
{
	m_flags |= Pop;
}

////////////////////////////////////////////////////////////////////////////////

void StateManager::initializeStates()
{
	if (m_active)
		return;

	for (auto &state : m_states)
		state->initialize();
	m_states.back()->activate();

	m_active = true;
}

void StateManager::updateStates()
{
	if (m_flags & Pop) {
		m_flags &= ~Pop;

		m_states.back()->deactivate();
		m_states.pop_back();

		if (m_flags & Swap) {
			m_flags &= ~Swap;

			m_states.push_back(std::move(m_swap));
			m_swap = nullptr;
		}

		m_states.back()->activate();
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
	std::list<State *> subset;

	auto it = m_states.rbegin();
	for (; it != m_states.rend(); ++it) {
		State *state = it->get();
		if (!state->isActive())
			state->activate();
		subset.push_back(state);
		if (state->isModal() || state->isFullscreen()) {
			++it;
			break;
		}
	}

	for (; it != m_states.rend(); ++it) {
		State *state = it->get();
		if (state->isActive())
			state->deactivate();
	}

	return subset;
}

std::list<State *> StateManager::getVisibleStates()
{
	std::list<State *> subset;

	auto it = m_states.end();
	do {
		--it;
	} while (it != m_states.begin() && !(*it)->isFullscreen());

	for (; it != m_states.end(); ++it)
		subset.push_back(it->get());

	return subset;
}