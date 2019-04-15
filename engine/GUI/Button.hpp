/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Button.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Button;
}

////////////////////////////////////////////////////////////////////////////////

#include "Widget.hpp"

#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Button : public Widget
{
public:
	Button(const std::string &id = "");
	Button(const std::string &id, const std::string &label);

public:
	void render(sf::RenderTarget &rt) override;

	void setLabel(const std::string &text, bool resize = true);
	const std::string getLabel() const;
	void setLabelSize(unsigned int size, bool resize = true);

	virtual void setSize(const sf::Vector2f &size);

private:
	void centerLabel();

	void onHoverIn_callback(sf::Vector2i);
	void onHoverOut_callback(sf::Vector2i);
	void onClick_callback(sf::Vector2i);
	void onRelease_callback(sf::Vector2i);

private:
	sf::Font m_font;
	sf::Text m_label;
};

}