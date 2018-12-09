/*
** EPITECH PROJECT, 2018
** R-Type client
** File description:
** Animation.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class AnimatedSprite;

////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Animation.hpp"

////////////////////////////////////////////////////////////////////////////////

class AnimatedSprite : public sf::Sprite
{
public:
	AnimatedSprite();

	void update(const sf::Time &elapsed);
	void reset();
	void setDefaultRect(sf::IntRect rect);

	void playAnimation(const std::string &name, bool loop = true, bool reset = true);
	void stopAnimation();
	template <class... Args>
	void addAnimation(const std::string &name, Args... frames)
	{
		Animation anim(*this);
		auto _ = {(anim.addFrame(frames),0)...};
		(void)_;

		m_animations.emplace(name, anim);
	}

private:
	std::map<std::string, Animation> m_animations;
	sf::IntRect m_defaultRect;
	Animation *m_currentAnimation;
	bool m_looped;
	bool m_resetOnFinish;
};