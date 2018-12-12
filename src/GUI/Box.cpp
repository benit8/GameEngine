/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Box.cpp
*/

#include "Box.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Box::Box()
: m_backgroundMode(Cover)
, m_backgroundAnim(nullptr)
{
	m_mode = Visible;
}

Box::~Box()
{
	if (m_backgroundAnim)
		delete m_backgroundAnim;
}

////////////////////////////////////////////////////////////////////////////////

void Box::update(const sf::Time &delta)
{
	if (m_backgroundAnim != nullptr) {
		m_backgroundAnim->update(delta);
		if (m_backgroundAnim->targetUpdate()) {
			if (!m_background.loadFromImage(m_backgroundAnim->currentFrame().image))
				std::cerr << "GUI::Box: Failed to update background" << std::endl;
			m_zone.setTexture(&m_background);
			m_backgroundAnim->resetTargetUpdate();
		}
	}

	sf::Vector2u imgSize = m_background.getSize();
	if (imgSize.x == 0 && imgSize.y == 0)
		return;

	sf::IntRect tRect(0, 0, imgSize.x, imgSize.y);
	float imageAspectRatio = (float)tRect.width / (float)tRect.height;
	float boxAspectRatio = width() / height();
	float diff = boxAspectRatio / imageAspectRatio;

	if (m_backgroundMode == Tiled) {
		sf::Vector2f f(width() / imgSize.x, height() / imgSize.y);
		tRect.width *= f.x;
		tRect.height *= f.y;
		tRect.left = -(width() - imgSize.x) / 2.f;
		tRect.top = -(height() - imgSize.y) / 2.f;
	}
	else if ((m_backgroundMode == Cover && boxAspectRatio < imageAspectRatio) ||
	         (m_backgroundMode == Contains && boxAspectRatio > imageAspectRatio)) {
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

void Box::draw(sf::RenderTarget &rt)
{
	rt.draw(m_zone);
}

////////////////////////////////////////////////////////////////////////////////

bool Box::setBackgroundImage(const std::string &path, BackgroundMode mode)
{
	if (path.rfind("gif") == path.length() - 3) {
		auto gif = new Graphics::GIF;
		if (!gif->loadFromFile(path)) {
			delete gif;
			return false;
		}
		return setBackgroundImage(gif, mode);
	}
	else {
		sf::Image image;
		if (!image.loadFromFile(path))
			return false;
		return setBackgroundImage(image, mode);
	}
}

bool Box::setBackgroundImage(const sf::Image &image, BackgroundMode mode)
{
	if (!m_background.loadFromImage(image)) {
		std::cerr << "Failed to load box background" << std::endl;
		return false;
	}

	m_backgroundMode = mode;
	m_background.setRepeated(m_backgroundMode == Tiled);
	m_zone.setTexture(&m_background);

	update(sf::Time::Zero);
	return true;
}

bool Box::setBackgroundImage(Graphics::GIF *gif, BackgroundMode mode)
{
	if (!m_background.loadFromImage(gif->frame(0).image)) {
		std::cerr << "Failed to load box background" << std::endl;
		return false;
	}

	m_backgroundMode = mode;
	m_background.setRepeated(m_backgroundMode == Tiled);
	m_zone.setTexture(&m_background);
	m_backgroundAnim = gif;
	m_backgroundAnim->play();

	update(sf::Time::Zero);
	return true;
}

void Box::setBackgroundMode(BackgroundMode mode)
{
	m_backgroundMode = mode;
	m_background.setRepeated(m_backgroundMode == Tiled);
	update(sf::Time::Zero);
}

void Box::setBackgroundColor(const sf::Color &color)
{
	m_zone.setFillColor(color);
}

void Box::setBorderColor(const sf::Color &color)
{
	m_zone.setOutlineColor(color);
}

void Box::setBorderSize(float size)
{
	m_zone.setOutlineThickness(size);
}

////////////////////////////////////////////////////////////////////////////////

}