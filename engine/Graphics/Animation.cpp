/*
** EPITECH PROJECT, 2018
** R-Type client
** File description:
** Animation.cpp
*/

#include <iostream>
#include "Animation.hpp"

////////////////////////////////////////////////////////////////////////////////

Animation::Animation(sf::Sprite &target)
: m_target(target)
, m_progress(sf::Time::Zero)
, m_nextProgressStep(sf::Time::Zero)
, m_frameIndex(0)
, m_finished(false)
{
}

////////////////////////////////////////////////////////////////////////////////

void Animation::addFrame(sf::IntRect rect, sf::Time duration)
{
	addFrame({rect, duration});
}

void Animation::addFrame(Frame frame)
{
	m_frames.push_back(frame);
}

void Animation::update(const sf::Time &elapsed, bool loop, bool reset)
{
	if (m_frames.empty()) {
		std::cerr << "Animation has no frames" << std::endl;
		return;
	}

	if (m_finished)
		return;

	if (m_nextProgressStep == sf::Time::Zero) {
		m_nextProgressStep = m_frames[0].duration;
	}

	m_progress += elapsed;
	if (m_progress >= m_nextProgressStep) {
		m_frameIndex++;

		if (m_frameIndex >= m_frames.size()) {
			if (loop) {
				m_frameIndex = 0;
				m_nextProgressStep = sf::Time::Zero;
			}
			else if (reset) {
				m_finished = true;
				m_frameIndex = 0;
				m_nextProgressStep = sf::Time::Zero;
			}
			else
				m_frameIndex--;
		}

		m_target.setTextureRect(m_frames[m_frameIndex].rect);
		m_nextProgressStep += m_frames[m_frameIndex].duration;
	}
}

void Animation::reset()
{
	m_progress = sf::Time::Zero;
	m_nextProgressStep = sf::Time::Zero;
	m_frameIndex = 0;
	m_finished = false;
}


const std::vector<Animation::Frame> &Animation::getFrames() const
{
	return m_frames;
}