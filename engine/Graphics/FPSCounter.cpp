/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** FPSCounter.cpp
*/

#include "FPSCounter.hpp"
#include "FontLoader.hpp"

////////////////////////////////////////////////////////////////////////////////

FPSCounter::FPSCounter(unsigned limit)
: m_limit(limit)
, m_frames(0)
, m_fps(0)
, m_counter(sf::Time::Zero)
, m_frameTime((m_limit > 0) ? sf::seconds(1.0 / (float)m_limit) : sf::Time::Zero)
, m_fpsTextFont(FontLoader::getDefault())
, m_fpsText("", m_fpsTextFont, 14)
, m_shouldDisplay(true)
{
	reset();
}

////////////////////////////////////////////////////////////////////////////////

void FPSCounter::reset()
{
	m_frames = 0;
	m_counter = sf::Time::Zero;
}

void FPSCounter::addFrameTime(const sf::Time &elapsed)
{
	m_counter += elapsed;

	if (m_counter >= sf::seconds(0.25f)) {
		m_fps = (float)m_frames / m_counter.asSeconds();
		reset();
	}
}

void FPSCounter::incrementFrameCount()
{
	m_frames++;
}

void FPSCounter::setLimit(unsigned limit)
{
	m_limit = limit;
	m_frameTime = (m_limit > 0) ? sf::seconds(1.0 / (float)m_limit) : sf::Time::Zero;
}

void FPSCounter::render(sf::RenderTarget &target)
{
	if (m_shouldDisplay) {
		m_fpsText.setString(std::to_string(m_fps) + " FPS");
		m_fpsText.setPosition(target.getSize().x - m_fpsText.getLocalBounds().width - 8, 4);
		target.draw(m_fpsText);
	}
}

void FPSCounter::toggleDisplay()
{
	m_shouldDisplay = !m_shouldDisplay;
}