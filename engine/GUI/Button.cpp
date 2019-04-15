/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Button.cpp
*/

#include "Button.hpp"
#include "../Application.hpp"
#include "../Graphics/FontLoader.hpp"
#include "GUI.hpp"
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Button::Button(const std::string &id)
: Widget(id)
{
	setMode(Clickable);
	setSize({30, 10});
	m_zone.setFillColor(sf::Color(0, 0, 0, 175));
	m_zone.setOutlineThickness(1);
	m_zone.setOutlineColor(sf::Color(170, 170, 170));

	m_font = FontLoader::getDefault();
	m_label.setFont(m_font);

	setLabel("Button");
	setLabelSize(18);

	onHoverIn.connect(this, &Button::onHoverIn_callback);
	onHoverOut.connect(this, &Button::onHoverOut_callback);
	onClick.connect(this, &Button::onClick_callback);
	onRelease.connect(this, &Button::onRelease_callback);
}

Button::Button(const std::string &id, const std::string &label)
: Button(id)
{
	setLabel(label);
}

////////////////////////////////////////////////////////////////////////////////

void Button::render(sf::RenderTarget &rt)
{
	rt.draw(m_zone);
	rt.draw(m_label);
}

////////////////////////////////////////////////////////////////////////////////

void Button::setLabel(const std::string &text, bool resize)
{
	m_label.setString(text);

	if (resize) {
		sf::FloatRect labelBounds = m_label.getLocalBounds();
		setSize({labelBounds.width + 32, labelBounds.height + 14});
	}

	centerLabel();
}

const std::string Button::getLabel() const
{
	return m_label.getString();
}

void Button::setLabelSize(unsigned int size, bool resize)
{
	m_label.setCharacterSize(size);

	if (resize) {
		sf::FloatRect labelBounds = m_label.getLocalBounds();
		setSize({labelBounds.width + 32, labelBounds.height + 14});
	}

	centerLabel();
}

void Button::setSize(const sf::Vector2f &requestedSize)
{
	sf::FloatRect labelBounds = m_label.getLocalBounds();
	sf::Vector2f size(requestedSize);
	size.x = std::max(size.x, labelBounds.width);
	size.y = std::max(size.y, labelBounds.height);

	Widget::setSize(size);
	centerLabel();
}


void Button::centerLabel()
{
	sf::FloatRect labelBounds = m_label.getLocalBounds();

	sf::Vector2f pos = getPosition();
	pos += sf::Vector2f((width() - labelBounds.width) / 2.f, (height() - labelBounds.height) / 2.f);
	pos -= sf::Vector2f(labelBounds.left, labelBounds.top);

	m_label.setPosition(pos);
}

////////////////////////////////////////////////////////////////////////////////

void Button::onHoverIn_callback(sf::Vector2i)
{
	m_zone.setOutlineColor(sf::Color::White);
	Application::instance()->window().setCursor(sf::Cursor::Hand);
}

void Button::onHoverOut_callback(sf::Vector2i)
{
	m_zone.setOutlineColor(sf::Color(170, 170, 170));
	Application::instance()->window().setCursor(sf::Cursor::Arrow);
}

void Button::onClick_callback(sf::Vector2i)
{
	m_zone.setFillColor(sf::Color::White);
	m_zone.setOutlineColor(sf::Color(170, 170, 170));
	m_label.setFillColor(sf::Color::Black);
}

void Button::onRelease_callback(sf::Vector2i)
{
	m_zone.setFillColor(sf::Color(0, 0, 0, 175));
	m_zone.setOutlineColor(sf::Color(170, 170, 170));
	m_label.setFillColor(sf::Color::White);
}

////////////////////////////////////////////////////////////////////////////////

}