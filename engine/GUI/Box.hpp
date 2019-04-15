/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Box.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Box;
}

////////////////////////////////////////////////////////////////////////////////

#include "Widget.hpp"
#include "../Graphics/GIF.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Box : public Widget
{
public:
	enum BackgroundMode
	{
		Contains,
		Cover,
		Tiled
	};

public:
	Box();
	~Box();

public:
	virtual void update(const sf::Time &) override;
	virtual void draw(sf::RenderTarget &rt) override;

public:
	bool setBackgroundImage(const std::string &path, BackgroundMode mode = Cover);
	bool setBackgroundImage(const sf::Image &image, BackgroundMode mode = Cover);
	void setBackgroundColor(const sf::Color &color);
	void setBackgroundMode(BackgroundMode mode);
	void setBorderColor(const sf::Color &color);
	void setBorderSize(float size);

private:
	bool setBackgroundImage(Graphics::GIF *gif, BackgroundMode mode);

private:
	sf::Texture m_background;
	BackgroundMode m_backgroundMode;
	Graphics::GIF *m_backgroundAnim;
};

}