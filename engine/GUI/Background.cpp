/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Background.cpp
*/

#include "Background.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Background::Background()
: m_bgMode(Cover)
, m_color(sf::Color::Transparent)
, m_anim(nullptr)
{
	m_mode = Visible;
	m_zone.setTexture(&m_texture);
}

Background::~Background()
{
	if (m_anim != nullptr)
		delete m_anim;
}

////////////////////////////////////////////////////////////////////////////////

void Background::update(const sf::Time &delta)
{
	m_zone.setFillColor(m_bgMode == Color ? m_color : sf::Color::White);
	if (m_bgMode == Color) // We don't need to do anything
		return;

	if (m_anim != nullptr) {
		m_anim->update(delta);
		if (m_anim->targetUpdate()) {
			if (!m_texture.loadFromImage(m_anim->currentFrame().image))
				std::cerr << "GUI::Background: Failed to update background" << std::endl;
			m_anim->resetTargetUpdate();
		}
	}

	sf::Vector2u imgSize = m_texture.getSize();
	if (imgSize.x == 0 && imgSize.y == 0)
		return;

	sf::IntRect tRect(0, 0, imgSize.x, imgSize.y);
	float imageAspectRatio = (float)tRect.width / (float)tRect.height;
	float boxAspectRatio = width() / height();
	float diff = boxAspectRatio / imageAspectRatio;

	if (m_bgMode == Tiled) {
		sf::Vector2f f(width() / imgSize.x, height() / imgSize.y);
		tRect.width *= f.x;
		tRect.height *= f.y;
		tRect.left = -(width() - imgSize.x) / 2.f;
		tRect.top = -(height() - imgSize.y) / 2.f;
	}
	else if ((m_bgMode == Cover && boxAspectRatio < imageAspectRatio) ||
	         (m_bgMode == Contains && boxAspectRatio > imageAspectRatio)) {
		int oldWidth = tRect.width;
		tRect.width *= diff;
		tRect.left = (oldWidth - tRect.width) / 2.f;
	}
	else {
		int oldHeight = tRect.height;
		tRect.height /= diff;
		tRect.top = (oldHeight - tRect.height) / 2.f;
	}

	m_zone.setTextureRect(tRect);
}

void Background::draw(sf::RenderTarget &rt)
{
	rt.draw(m_zone);
}

void Background::resize(sf::Vector2u size)
{
	setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
}

////////////////////////////////////////////////////////////////////////////////

void Background::setColor(const sf::Color &color)
{
	m_color = color;
}

bool Background::setImage(const std::string &path, BGMode mode)
{
	if (path.rfind("gif") == path.length() - 3) {
		auto gif = new Graphics::GIF;
		if (!gif->loadFromFile(path)) {
			delete gif;
			return false;
		}
		return setImage(gif, mode);
	}
	else {
		sf::Image image;
		if (!image.loadFromFile(path))
			return false;
		return setImage(image, mode);
	}
}

bool Background::setImage(const sf::Image &image, BGMode mode)
{
	if (!m_texture.loadFromImage(image)) {
		std::cerr << "Failed to load image background" << std::endl;
		return false;
	}

	if (m_anim) {
		delete m_anim;
		m_anim = nullptr;
	}

	m_bgMode = mode;
	m_texture.setRepeated(m_bgMode == Tiled);

	update(sf::Time::Zero);
	return true;
}

bool Background::setImage(Graphics::GIF *gif, BGMode mode)
{
	if (!m_texture.loadFromImage(gif->frame(0).image)) {
		std::cerr << "Failed to load image background" << std::endl;
		return false;
	}

	if (m_anim) {
		delete m_anim;
		m_anim = nullptr;
	}

	m_bgMode = mode;
	m_texture.setRepeated(m_bgMode == Tiled);
	m_anim = gif;
	m_anim->play();

	update(sf::Time::Zero);
	return true;
}

void Background::setMode(BGMode mode)
{
	m_bgMode = mode;
	m_texture.setRepeated(m_bgMode == Tiled);
	m_zone.setTexture(m_bgMode == Color ? nullptr : &m_texture);
	update(sf::Time::Zero);
}

////////////////////////////////////////////////////////////////////////////////

}