/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Background.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Background;
}

////////////////////////////////////////////////////////////////////////////////

#include "Widget.hpp"
#include "Graphics/GIF.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Background : public Widget
{
public:
	enum BGMode
	{
		Contains,
		Cover,
		Tiled,
		Color
	};

public:
	Background();
	~Background();

public:
	void update(const sf::Time &) override;
	void draw(sf::RenderTarget &rt) override;
	void resize(sf::Vector2u size);

public:
	void setColor(const sf::Color &color);
	bool setImage(const std::string &path, BGMode mode = Cover);
	bool setImage(const sf::Image &image, BGMode mode = Cover);
	void setMode(BGMode mode);

private:
	bool setImage(Graphics::GIF *gif, BGMode mode);

private:
	BGMode m_bgMode;
	sf::Color m_color;
	sf::Texture m_texture;
	Graphics::GIF *m_anim;
};

}