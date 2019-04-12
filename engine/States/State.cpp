/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** States / State.cpp
*/

#include "State.hpp"

////////////////////////////////////////////////////////////////////////////////

State::State(const std::string &name)
: m_name(name)
, m_guiContext(ImGui::CreateContext(ImGui::GetCurrentContext() ? ImGui::GetIO().Fonts : NULL))
{
}

State::~State()
{
}

////////////////////////////////////////////////////////////////////////////////

void State::initialize()
{
	if (m_initialized)
		return;
	m_initialized = true;

	ImGuiContext *_prevContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(m_guiContext);
	onInitialize();
	ImGui::SetCurrentContext(_prevContext);
}

void State::handleEvent(const sf::Event &e)
{
	ImGuiContext *_prevContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(m_guiContext);

	ImGui::SFML::ProcessEvent(e);
	m_events.dispatchEvent(e);

	ImGui::SetCurrentContext(_prevContext);
}

void State::update(const sf::Time &delta, sf::RenderWindow &window, bool updateGui)
{
	ImGuiContext *_prevContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(m_guiContext);

	if (updateGui)
		ImGui::SFML::Update(window, delta);
	else
		ImGui::NewFrame();
	onUpdate(delta);
	ImGui::EndFrame();

	ImGui::SetCurrentContext(_prevContext);
}

void State::staticUpdate(const sf::Time &delta)
{
	ImGuiContext *_prevContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(m_guiContext);

	onStaticUpdate(delta);

	ImGui::SetCurrentContext(_prevContext);
}

void State::render(sf::RenderTarget &renderTarget)
{
	ImGuiContext *_prevContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(m_guiContext);

	onRender(renderTarget);
	ImGui::SFML::Render(renderTarget);

	ImGui::SetCurrentContext(_prevContext);
}

void State::activate()
{
	if (m_active)
		return;
	m_active = true;
	onActivate();
}

void State::deactivate()
{
	if (!m_active)
		return;
	m_active = false;
	onDeactivate();
}