/*
** EPITECH PROJECT, 2018
** R-Type client
** File description:
** AnimatedSprite.cpp
*/

#include "AnimatedSprite.hpp"

////////////////////////////////////////////////////////////////////////////////

AnimatedSprite::AnimatedSprite()
: m_currentAnimation(nullptr)
, m_looped(true)
, m_resetOnFinish(true)
{
}

////////////////////////////////////////////////////////////////////////////////

void AnimatedSprite::update(const sf::Time &elapsed)
{
	if (!m_currentAnimation)
		return;

	m_currentAnimation->update(elapsed, m_looped, m_resetOnFinish);
}

void AnimatedSprite::reset()
{
	m_currentAnimation = nullptr;
	setTextureRect(m_defaultRect);
}

void AnimatedSprite::setDefaultRect(sf::IntRect rect)
{
	m_defaultRect = rect;
}

void AnimatedSprite::playAnimation(const std::string &name, bool loop, bool reset)
{
	auto it = m_animations.find(name);
	if (it == m_animations.end() || &it->second == m_currentAnimation)
		return;

	m_currentAnimation = &(it->second);
	m_currentAnimation->reset();
	m_looped = loop;
	m_resetOnFinish = reset;
}

void AnimatedSprite::stopAnimation()
{
	m_currentAnimation = nullptr;
	reset();
}