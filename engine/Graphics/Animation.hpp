/*
** EPITECH PROJECT, 2018
** R-Type client
** File description:
** Animation.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

////////////////////////////////////////////////////////////////////////////////

class Animation
{
public:
	struct Frame
	{
		Frame(sf::IntRect r, sf::Time d)
		: rect(r)
		, duration(d)
		{}

		sf::IntRect rect;
		sf::Time duration;
	};

public:
	Animation(sf::Sprite &target);

	void addFrame(sf::IntRect rect, sf::Time duration);
	void addFrame(Frame frame);
	void update(const sf::Time &elapsed, bool update, bool reset);
	void reset();

	const std::vector<Frame> &getFrames() const;

private:
	sf::Sprite &m_target;
	std::vector<Frame> m_frames;
	sf::Time m_progress;
	sf::Time m_nextProgressStep;
	std::size_t m_frameIndex;
	bool m_finished;
};