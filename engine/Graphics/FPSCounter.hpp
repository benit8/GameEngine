/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** FPSCounter.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class FPSCounter;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

////////////////////////////////////////////////////////////////////////////////

class FPSCounter
{
public:
	FPSCounter(unsigned limit = 120);

public:
	void reset();
	void addFrameTime(const sf::Time &elapsed);
	void incrementFrameCount();
	void setLimit(unsigned limit);
	void render(sf::RenderTarget &rt);
	void toggleDisplay();

	unsigned getFPS() const { return m_fps; }
	unsigned getLimit() const { return m_limit; }
	const sf::Time &getFrameTime() const { return m_frameTime; }

	FPSCounter &operator ++(int) { incrementFrameCount(); return *this; }
	FPSCounter &operator +=(const sf::Time &elapsed) { addFrameTime(elapsed); return *this; }

private:
	unsigned m_limit, m_frames, m_fps;
	sf::Time m_counter;
	sf::Time m_frameTime;

	sf::Font m_fpsTextFont;
	sf::Text m_fpsText;
	bool m_shouldDisplay;
};