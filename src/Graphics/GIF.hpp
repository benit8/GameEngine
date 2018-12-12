/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Graphics / GIF.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Graphics {
	class GIF;
}

////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "extern/stb_gif.h"

////////////////////////////////////////////////////////////////////////////////

namespace Graphics
{

class GIF
{
public:
	struct Frame
	{
		Frame(const sf::Vector2u &size, uint8_t *data, uint16_t delay)
		: size(size)
		, duration(sf::milliseconds(delay))
		{
			image.create(size.x, size.y, data);
		}

		sf::Vector2u size;
		sf::Time duration;
		sf::Image image;
	};

public:
	GIF();
	~GIF();

public:
	bool loadFromFile(const std::string &filename);

	void play();
	void stop();
	void update(const sf::Time &delta);

	const sf::Vector2u &size() const { return m_size; }
	int width() const { return m_size.x; }
	int height() const { return m_size.y; }
	std::size_t frameCount() { return m_frames.size(); }
	Frame &frame(std::size_t pos) { return *m_frames[pos]; }
	Frame &currentFrame() { return *m_frames[m_currentFrame]; }
	Frame &operator [](std::size_t pos) { return *m_frames[pos]; }
	bool targetUpdate() const { return m_targetUpdate; }
	void resetTargetUpdate() { m_targetUpdate = false; }

	// operator sf::Texture() {
	// 	sf::Texture texture;
	// 	texture.loadFromImage(m_frames[m_currentFrame]);
	// 	return texture;
	// }

private:
	sf::Vector2u m_size;
	std::vector<Frame *> m_frames;
	bool m_playing;
	sf::Time m_progress;
	sf::Time m_nextProgressStep;
	std::size_t m_currentFrame;
	bool m_targetUpdate;
};

}