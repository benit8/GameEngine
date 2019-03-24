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
		Tiled
	};

public:
	Background();
	~Background();

public:
	virtual void update(const sf::Time &) override;
	virtual void draw(sf::RenderTarget &rt) override;
	void resize(sf::Vector2u size);

public:
	bool setImage(const std::string &path, BGMode mode = Cover);
	bool setImage(const sf::Image &image, BGMode mode = Cover);
	void setMode(BGMode mode);

private:
	bool setImage(Graphics::GIF *gif, BGMode mode);

private:
	sf::Texture m_texture;
	BGMode m_bgMode;
	Graphics::GIF *m_anim;
};

}