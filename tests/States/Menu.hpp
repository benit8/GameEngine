/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** Menu.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <memory>

#include "GUI/Background.hpp"
#include "States/State.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

////////////////////////////////////////////////////////////////////////////////

class Menu : public State
{
public:
	Menu()
	{
		m_events.onKeyDown(std::bind(&Application::close, Application::instance()), sf::Keyboard::Escape);

		onInitialize.connect(this, &Menu::initialize);
		onUpdate.connect(this, &Menu::makeGUI);
	}

public:
	void initialize()
	{
		ImGuiIO &io = ImGui::GetIO();
		m_font = io.Fonts->AddFontFromFileTTF("tests/assets/Consolas.ttf", 16.0f);
		// io.Fonts->Build();
		ImGui::SFML::UpdateFontTexture();

		m_bg = std::make_unique<GUI::Background>();
		m_bg->setImage("tests/assets/waterfall.gif");
		onUpdate.connect(m_bg.get(), &GUI::Background::update);
		onRender.connect((GUI::Widget *)m_bg.get(), &GUI::Widget::render);
		m_events.onResize(std::bind(&GUI::Background::resize, m_bg.get(), _1));
	}

	void makeGUI(const sf::Time &)
	{
		// ImGui::GetIO().FontGlobalScale = 1.25f;

		ImGui::SetNextWindowPosCenter();
		ImGui::SetNextWindowSize({400, 200});
		ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoDecoration);
			ImGui::PushFont(m_font);
			ImGui::InputText("Window title", m_text, 255);

			if (ImGui::Button("Update window title")) {
				Application::instance()->window().title(std::string(m_text));
			}
			ImGui::PopFont();
		ImGui::End();
	}

private:
	std::unique_ptr<GUI::Background> m_bg;
	ImFont *m_font = nullptr;
	char m_text[255] = {0};
};

////////////////////////////////////////////////////////////////////////////////

}