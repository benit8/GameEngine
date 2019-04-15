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
#include "../Graphics/GIF.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Background : public Widget
{
public:
	enum BackgroundMode
	{
		Contains,
		Cover,
		Tiled,
		Color
	};

public:
	Background(const std::string &id = "");
	~Background();

public:
	void update(const sf::Time &) override;
	void render(sf::RenderTarget &rt) override;
	void resize(sf::Vector2u size);

public:
	void setColor(const sf::Color &color);
	bool setImage(const std::string &path, BackgroundMode mode = Cover);
	bool setImage(const sf::Image &image, BackgroundMode mode = Cover);
	void setBackgroundMode(BackgroundMode mode);

private:
	bool setImage(Graphics::GIF *gif, BackgroundMode mode);

private:
	BackgroundMode m_bgMode;
	sf::Color m_color;
	sf::Texture m_texture;
	Graphics::GIF *m_anim;
};

}